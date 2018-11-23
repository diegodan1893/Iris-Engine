#include "CharacterObject.h"
#include "Locator.h"
#include "Sprite.h"
#include "IRenderer.h"
#include "ITexture.h"
#include "DissolveShader.h"
#include "ColorGradingShader.h"
#include <cmath>

CharacterObject::CharacterObject(IRenderer* renderer, const std::string& baseFile, Alignment position, int zindex)
	:Object(zindex),
	 separator(Config::values().paths.separator),
	 sizeWasSet(false),
	 inDissolveBase(false),
	 transitionTextureHasBeenUpdated(false),
	 colorGradingEnabled(false),
	 blendLUTs(false),
	 renderer(renderer),
	 transitionTexture(nullptr),
	 dissolveBaseTransitionTexture(nullptr),
	 dissolveBaseFinalTexture(nullptr)
{
	setUp(baseFile);
	setCharacterPosition(position);
}

CharacterObject::CharacterObject(IRenderer* renderer, const std::string& baseFile, Vector2<float> position, int zindex)
	:Object(zindex),
	 separator(Config::values().paths.separator),
	 sizeWasSet(false),
	 inDissolveBase(false),
	 transitionTextureHasBeenUpdated(false),
	 colorGradingEnabled(false),
	 blendLUTs(false),
	 renderer(renderer),
	 transitionTexture(nullptr),
	 dissolveBaseTransitionTexture(nullptr),
	 dissolveBaseFinalTexture(nullptr)
{
	setUp(baseFile);
	setPosition(position);
}

CharacterObject::~CharacterObject()
{
	freeTransitionTextures();
}

void CharacterObject::draw(IRenderer* renderer)
{
	if (valid() && visible())
	{
		if (inFade())
		{
			// Currently in the middle of a fade: draw transition texture
			renderer->copy(transitionTexture, nullptr, &getRect());
		}
		else if (inDissolveBase)
		{
			// Currently in the middle of a base dissolve
			DissolveShader* dissolveShader = renderer->getDissolveShader();
			dissolveShader->bind();
			
			// Texture needs to be set every draw to allow multiple characters
			// to fade at the same time
			dissolveShader->setParameters(transitionTexture, getDissolveAlpha() / 255.0);

			Rect<float> rect;
			rect.x = 0;
			rect.y = 0;
			rect.w = getRect().w;
			rect.h = getRect().h;

			// Draw character to intermediate texture
			renderer->setRenderTarget(dissolveBaseFinalTexture);
			renderer->clear();
			renderer->copy(dissolveBaseTransitionTexture, nullptr, &rect);
			renderer->setRenderTarget(nullptr);

			dissolveShader->unbind();

			// Draw intermediate texture to screen applying color grading
			ColorGradingShader* colorGradingShader = renderer->getColorGradingShader();

			if (colorGradingEnabled)
				setUpLutShader(colorGradingShader);

			renderer->copy(dissolveBaseFinalTexture, nullptr, &getRect());

			colorGradingShader->unbind();
		}
		else
		{
			// No transition or expression dissolve
			drawCharacter(getRect(), false);
		}
	}
}

void CharacterObject::update(float elapsedSeconds)
{
	if (valid())
	{
		// Update complete object transitions
		if (inFade())
		{
			updateAlpha(elapsedSeconds);

			// In order to fade in or out without weird artifacts caused by
			// drawing several layers with the same alpha on top of each
			// other, we need to prerender the character and its expression
			// to a texture and fade that texture.
			if (!transitionTextureHasBeenUpdated || lutTransition.inTransition())
			{
				redrawTransitionTexture(transitionTexture);
				transitionTextureHasBeenUpdated = true;
			}

			transitionTexture->setAlphaMod(getAlpha());
		}
		else
		{
			if (transitionTextureHasBeenUpdated)
			{
				// Character just finished fading
				transitionTextureHasBeenUpdated = false;
			}
		}

		// Update dissolve transition for expressions
		if (inDissolve())
		{
			updateDissolveAlpha(elapsedSeconds);
		}
		else
		{
			if (inDissolveBase)
			{
				// Base dissolve just finished
				inDissolveBase = false;
			}
		}

		// Update move transitions
		if (inMovement())
			updateMovement(elapsedSeconds);

		// Update LUT transitions
		if (lutTransition.inTransition())
		{
			lutTransition.update(elapsedSeconds);

			if (!lutTransition.inTransition())
			{
				if (lutTransition.getStep() == 0.0f)
					colorGradingEnabled = false;

				blendLUTs = false;
			}
		}
	}
}

void CharacterObject::setCharacterPosition(Alignment position)
{
	setPosition(calculatePosition(position));
}

void CharacterObject::moveToCharacterPosition(Alignment position, float time, bool canBeSkipped, class Interpolator* interpolator)
{
	move(calculatePosition(position), time, canBeSkipped, interpolator);
}

void CharacterObject::setExpression(const std::string& expression)
{
	this->expression = expression;
}

void CharacterObject::setExpressionBase(const std::string& expressionBase)
{
	this->expressionBase = Config::values().paths.characters;

	// Split filename into base and extension
	size_t extIndex = expressionBase.find_last_of('.');

	if (extIndex != std::string::npos && extIndex < expressionBase.size() - 1)
	{
		// Filename has an extension
		fileExtension = expressionBase.substr(extIndex);
		this->expressionBase += expressionBase.substr(0, extIndex);
	}
	else
	{
		this->expressionBase += expressionBase;
	}
}

void CharacterObject::setBase(const std::string& base, const std::string& expressionBase)
{
	basePath = Config::values().paths.characters + base;
	setExpressionBase(expressionBase);
}

void CharacterObject::startDissolveExpression(const std::string& expression, float time, bool canBeSkipped)
{
	if (inFade() || inDissolve())
	{
		skipTransition();
		setVisible(true);
	}

	previousExpression = this->expression;
	setExpression(expression);

	startDissolve(time, canBeSkipped);
	inDissolveBase = false;
}

void CharacterObject::startDissolveBase(
	const std::string& base,
	const std::string& expressionBase,
	const std::string& expression,
	float time,
	bool canBeSkipped
)
{
	if (inFade() || inDissolve())
	{
		skipTransition();
		setVisible(true);
	}

	// Create an intermediate texture with the current base and expression
	// so that we can use alpha blending without weird artifacts
	redrawTransitionTexture(transitionTexture, false);

	// Create an intermediate texture with the new base and expression
	setBase(base, expressionBase);
	setExpression(expression);
	redrawTransitionTexture(dissolveBaseTransitionTexture, false);

	startDissolve(time, canBeSkipped);
	inDissolveBase = true;
}

void CharacterObject::setColorLut(const std::string& colorLUT, float time)
{
	if (colorGradingEnabled)
	{
		previousColorLUT = this->colorLUT;
		blendLUTs = true;
	}
	else
	{
		blendLUTs = false;
	}

	this->colorLUT = Config::values().paths.luts + colorLUT;
	colorGradingEnabled = true;
	transitionTextureHasBeenUpdated = false;

	lutTransition.start(time, false);
}

void CharacterObject::disableColorGrading(float time)
{
	blendLUTs = false;
	lutTransition.start(time, true);
}

void CharacterObject::setUp(const std::string& baseFile)
{
	// Set base path
	basePath = Config::values().paths.characters + baseFile;

	// Set expression base to the same base file
	setExpressionBase(baseFile);

	// Precache if necessary
	if (Config::values().cache.allowPrecaching)
	{
		Sprite* sprite = Locator::getCache()->getSprite(basePath);

		if (sprite)
			initializeSize(sprite->getTextureSize().x, sprite->getTextureSize().y);
		else
			setValid(false);
	}
}

void CharacterObject::centerOrigin()
{
	Rect<float> rect = getRect();
	setOrigin(rect.w / 2, rect.h);
}

void CharacterObject::initializeSize(int w, int h)
{
	// Set the size and center the sprite
	setSize(w, h);
	centerOrigin();
	sizeWasSet = true;

	// Create transition textures
	freeTransitionTextures();

	transitionTexture = renderer->createTexture(TextureFormat::RGBA8, TextureAccess::TARGET, w, h);
	transitionTexture->setBlendMode(BlendMode::BLEND);

	dissolveBaseTransitionTexture = renderer->createTexture(TextureFormat::RGBA8, TextureAccess::TARGET, w, h);
	dissolveBaseTransitionTexture->setBlendMode(BlendMode::SET);

	dissolveBaseFinalTexture = renderer->createTexture(TextureFormat::RGBA8, TextureAccess::TARGET, w, h);
	dissolveBaseFinalTexture->setBlendMode(BlendMode::BLEND);
}

void CharacterObject::drawCharacter(Rect<float>& rect, bool drawWithoutBlending, bool applyColorGrading)
{
	// Activate color grading shader
	ColorGradingShader* colorGradingShader = renderer->getColorGradingShader();

	if (colorGradingEnabled && applyColorGrading)
	{
		setUpLutShader(colorGradingShader);
	}

	// Get base
	Sprite* baseSprite = Locator::getCache()->getSprite(basePath);

	if (baseSprite)
	{
		if (!sizeWasSet)
			initializeSize(baseSprite->getTextureSize().x, baseSprite->getTextureSize().y);

		ITexture* baseTexture = baseSprite->getTexture();

		// Draw base
		if (baseTexture)
		{
			if (drawWithoutBlending)
			{
				baseTexture->setBlendMode(BlendMode::SET);
				renderer->copy(baseTexture, nullptr, &rect);
				baseTexture->setBlendMode(BlendMode::BLEND);
			}
			else
			{
				renderer->copy(baseTexture, nullptr, &rect);
			}
		}

		// Draw expression
		if (inDissolve() && !inFade())
		{
			drawExpression(previousExpression, rect, 255);
			drawExpression(expression, rect, getDissolveAlpha());
		}
		else
		{
			drawExpression(expression, rect, 255);
		}
	}
	else
	{
		// Avoid showing an error message every frame
		setValid(false);
	}

	// Unbind color grading shader
	if (colorGradingEnabled)
		colorGradingShader->unbind();
}

void CharacterObject::drawExpression(const std::string& expression, Rect<float>& rect, Uint8 alpha)
{
	Sprite* expressionSprite = Locator::getCache()->getSprite(expressionBase + separator + expression + fileExtension);

	if (expressionSprite)
	{
		ITexture* expressionTexture = expressionSprite->getTexture();

		// Draw expression
		if (expressionTexture)
		{
			expressionTexture->setBlendMode(BlendMode::KEEP_ALPHA);
			expressionTexture->setAlphaMod(alpha);
			renderer->copy(expressionTexture, nullptr, &rect);
		}
	}
	else
	{
		// Avoid showing an error message every frame
		setValid(false);
	}
}

void CharacterObject::redrawTransitionTexture(ITexture* texture, bool applyColorGrading)
{
	Sprite* baseSprite = Locator::getCache()->getSprite(basePath);

	if (baseSprite)
	{
		if (!sizeWasSet)
			initializeSize(baseSprite->getTextureSize().x, baseSprite->getTextureSize().y);

		Rect<float> rect;
		rect.x = 0;
		rect.y = 0;
		rect.w = getRect().w;
		rect.h = getRect().h;

		// Start rendering to texture
		renderer->setRenderTarget(texture);
		renderer->clear();

		// Draw character without blending the base to avoid applying alpha twice
		drawCharacter(rect, true, applyColorGrading);

		// Stop rendering to texture
		renderer->setRenderTarget(nullptr);
	}
}

Vector2<float> CharacterObject::calculatePosition(Alignment position)
{
	Vector2<float> actualPosition(0, Config::values().screen.resolution.y);

	switch (position)
	{
	case Alignment::LEFT:
		actualPosition.x = getRect().w / 2;
		break;

	case Alignment::CENTER:
		actualPosition.x = Config::values().screen.resolution.x / 2;
		break;

	case Alignment::RIGHT:
		actualPosition.x = Config::values().screen.resolution.x - getRect().w / 2;
		break;

	default:
		Locator::getLogger()->log(LogCategory::OBJECT, LogPriority::ERROR, "Invalid character position.");
		break;
	}

	return actualPosition;
}

void CharacterObject::freeTransitionTextures()
{
	if (transitionTexture)
		delete transitionTexture;

	if (dissolveBaseTransitionTexture)
		delete dissolveBaseTransitionTexture;

	if (dissolveBaseFinalTexture)
		delete dissolveBaseFinalTexture;
}

void CharacterObject::setUpLutShader(ColorGradingShader* colorGradingShader)
{
	Sprite* colorLUTSprite = Locator::getCache()->getSprite(colorLUT);

	if (colorLUTSprite)
	{
		colorGradingShader->bind();

		if (lutTransition.inTransition())
		{
			if (blendLUTs)
			{
				Sprite* previousColorLUTSprite = Locator::getCache()->getSprite(previousColorLUT);

				if (previousColorLUTSprite)
					colorGradingShader->setParameters(previousColorLUTSprite->getTexture(), colorLUTSprite->getTexture(), lutTransition.getStep());
				else
					blendLUTs = false;
			}
			else
			{
				colorGradingShader->setParameters(colorLUTSprite->getTexture(), lutTransition.getStep());
			}
		}
		else
		{
			colorGradingShader->setParameters(colorLUTSprite->getTexture());
		}
	}
	else
	{
		colorGradingEnabled = false;
		lutTransition.skip();
	}
}
