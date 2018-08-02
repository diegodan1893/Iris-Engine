#include "LuaCharacterSprite.h"
#include "CharacterObject.h"
#include "GameObjectManager.h"
#include "WaitQueue.h"
#include "WaitForTransition.h"
#include "Locator.h"
#include "TransitionUtils.h"
#include "LuaEnvironment.h"

LuaCharacterSprite::LuaCharacterSprite(
	class IRenderer* renderer,
	GameObjectManager* gom,
	LuaEnvironment* lua,
	const std::string& baseFile,
	Alignment position,
	int zindex
)
	:gameObjectManager(gom),
	 lua(lua)
{
	// Create character objcet
	character = new CharacterObject(renderer, baseFile, position, zindex);

	// Add object to game manager
	gameObjectManager->add(character);
}

LuaCharacterSprite::LuaCharacterSprite(
	class IRenderer* renderer,
	GameObjectManager* gom,
	LuaEnvironment* lua,
	const std::string& baseFile,
	Vector2<float> position,
	int zindex
)
	:gameObjectManager(gom),
	 lua(lua)
{
	// Create character objcet
	character = new CharacterObject(renderer, baseFile, position, zindex);

	// Add object to game manager
	gameObjectManager->add(character);
}

LuaCharacterSprite::~LuaCharacterSprite()
{
	// Remove object from game object manager and delete it
	bool success = gameObjectManager->remove(character);

	if (success)
		delete character;

	// Can't log because logger may not exist at this point
}

void LuaCharacterSprite::show(const std::string& expression)
{
	if (!character->visible())
	{
		// By default, character sprites show with a non-blocking 0.3 seconds fade
		character->setExpression(expression);
		character->startFadeIn(0.3f, false);
	}
	else
	{
		// By default, character sprites change expression with a non-blocking 0.3 seconds dissolve
		character->startDissolveExpression(expression, 0.3f, false);
	}
}

void LuaCharacterSprite::showTransition(const std::string& expression, const sol::table& transition, sol::this_state s)
{
	TransitionType transitionType;

	if (TransitionUtils::getTransitionType(transition, transitionType))
	{
		switch (transitionType)
		{
		case TransitionType::NONE:
			character->setExpression(expression);
			character->setVisible(true);
			break;

		case TransitionType::FADE:
			float transitionTime;
			bool shouldBlock;

			if (TransitionUtils::getTransitionTime(transition, transitionTime) &&
				TransitionUtils::getTransitionBlocking(transition, shouldBlock))
			{
				character->setExpression(expression);
				character->startFadeIn(transitionTime, shouldBlock);

				if (shouldBlock)
				{
					lua->waitFor(new WaitForTransition(character));
					lua_yield(s, 0);
				}
			}

			break;

		case TransitionType::DISSOLVE:
			if (character->visible())
			{
				float transitionTime;
				bool shouldBlock;

				if (TransitionUtils::getTransitionTime(transition, transitionTime) &&
					TransitionUtils::getTransitionBlocking(transition, shouldBlock))
				{
					character->startDissolveExpression(expression, transitionTime, shouldBlock);

					if (shouldBlock)
					{
						lua->waitFor(new WaitForTransition(character));
						lua_yield(s, 0);
					}
				}
			}
			else
			{
				Locator::getLogger()->log(
					LogCategory::LUA,
					LogPriority::ERROR,
					u8"Dissolve transition can only be used if the sprite was already visible"
				);
			}

			break;

		default:
			Locator::getLogger()->log(
				LogCategory::LUA,
				LogPriority::ERROR,
				u8"Invalid transition type for method 'show' of CharacterSprite"
			);

			break;
		}
	}
}

void LuaCharacterSprite::hide()
{
	// By default, character sprites hide with a non-blocking 0.3 seconds fade
	character->startFadeOut(0.3f, false);
}

void LuaCharacterSprite::hideTransition(const sol::table& transition, sol::this_state s)
{
	TransitionType transitionType;

	if (TransitionUtils::getTransitionType(transition, transitionType))
	{
		switch (transitionType)
		{
		case TransitionType::NONE:
			character->setVisible(false);
			break;

		case TransitionType::FADE:
			float transitionTime;
			bool shouldBlock;

			if (TransitionUtils::getTransitionTime(transition, transitionTime) &&
				TransitionUtils::getTransitionBlocking(transition, shouldBlock))
			{
				character->startFadeOut(transitionTime, shouldBlock);

				if (shouldBlock)
				{
					lua->waitFor(new WaitForTransition(character));
					lua_yield(s, 0);
				}
			}

			break;

		default:
			Locator::getLogger()->log(
				LogCategory::LUA,
				LogPriority::ERROR,
				u8"Invalid transition type for method 'hide' of CharacterSprite"
			);

			break;
		}
	}
}

void LuaCharacterSprite::setBase(const std::string& base, const std::string& expressionBase, const std::string& expression)
{
	if (!character->visible())
	{
		character->setBase(base, expressionBase);
		character->setExpression(expression);
	}
	else
	{
		// By default, character sprites change base with a non-blocking 0.3 seconds dissolve
		character->startDissolveBase(base, expressionBase, expression, 0.3f, false);
	}
}

void LuaCharacterSprite::setBaseTransition(
	const std::string& base,
	const std::string& expressionBase,
	const std::string& expression,
	const sol::table& transition,
	sol::this_state s)
{
	TransitionType transitionType;

	if (TransitionUtils::getTransitionType(transition, transitionType))
	{
		switch (transitionType)
		{
		case TransitionType::NONE:
			character->setBase(base, expressionBase);
			character->setExpression(expression);
			break;

		case TransitionType::DISSOLVE:
			if (character->visible())
			{
				float transitionTime;
				bool shouldBlock;

				if (TransitionUtils::getTransitionTime(transition, transitionTime) &&
					TransitionUtils::getTransitionBlocking(transition, shouldBlock))
				{
					character->startDissolveBase(base, expressionBase, expression, transitionTime, shouldBlock);

					if (shouldBlock)
					{
						lua->waitFor(new WaitForTransition(character));
						lua_yield(s, 0);
					}
				}
			}
			else
			{
				Locator::getLogger()->log(
					LogCategory::LUA,
					LogPriority::ERROR,
					u8"Dissolve transition can only be used if the sprite was already visible"
				);
			}

			break;

		default:
			Locator::getLogger()->log(
				LogCategory::LUA,
				LogPriority::ERROR,
				u8"Invalid transition type for method 'setBase' of CharacterSprite"
			);

			break;
		}
	}
}

void LuaCharacterSprite::skipTransition()
{
	character->skipTransition();
}

void LuaCharacterSprite::setPosition(float x, float y)
{
	character->skipMovement();
	character->setPosition(x, y);
}

void LuaCharacterSprite::setPositionX(float x)
{
	character->skipMovement();
	character->setPosition(x, Config::values().screen.resolution.y);
}

void LuaCharacterSprite::setCharacterPosition(Alignment position)
{
	character->skipMovement();
	character->setCharacterPosition(position);
}

void LuaCharacterSprite::move(float x, float y, float time, bool shouldBlock, sol::this_state s)
{
	moveInterpolator(x, y, time, shouldBlock, InterpolatorType::DEFAULT, s);
}

void LuaCharacterSprite::moveInterpolator(
	float x,
	float y,
	float time,
	bool shouldBlock,
	InterpolatorType interpolator,
	sol::this_state s
)
{
	character->move(x, y, time, shouldBlock, TransitionUtils::getInterpolator(interpolator));

	if (shouldBlock)
	{
		lua->waitFor(new WaitForTransition(character));
		lua_yield(s, 0);
	}
}

void LuaCharacterSprite::moveX(float x, float time, bool shouldBlock, sol::this_state s)
{
	moveXInterpolator(x, time, shouldBlock, InterpolatorType::DEFAULT, s);
}

void LuaCharacterSprite::moveXInterpolator(
	float x,
	float time,
	bool shouldBlock,
	InterpolatorType interpolator,
	sol::this_state s
)
{
	moveInterpolator(x, Config::values().screen.resolution.y, time, shouldBlock, interpolator, s);
}

void LuaCharacterSprite::movePosition(Alignment position, float time, bool shouldBlock, sol::this_state s)
{
	movePositionInterpolator(position, time, shouldBlock, InterpolatorType::DEFAULT, s);
}

void LuaCharacterSprite::movePositionInterpolator(
	Alignment position,
	float time,
	bool shouldBlock,
	InterpolatorType interpolator,
	sol::this_state s
)
{
	character->moveToCharacterPosition(position, time, shouldBlock, TransitionUtils::getInterpolator(interpolator));

	if (shouldBlock)
	{
		lua->waitFor(new WaitForTransition(character));
		lua_yield(s, 0);
	}
}

void LuaCharacterSprite::setExpressionBase(const std::string& expressionBase)
{
	if (character->visible())
	{
		character->setVisible(false);
		Locator::getLogger()->log(
			LogCategory::LUA,
			LogPriority::WARNING,
			"Trying to change the expressions base of a visible character."
		);
	}

	character->setExpressionBase(expressionBase);
}

