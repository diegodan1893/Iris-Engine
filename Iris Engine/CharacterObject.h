#pragma once

#include "Object.h"
#include "Alignment.h"
#include "Config.h"
#include <string>

/// <summary>
/// A character sprite.
/// </summary>
/// <seealso cref="Object" />
class CharacterObject : public Object
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="CharacterObject"/> class.
	/// </summary>
	/// <param name="renderer">The renderer.</param>
	/// <param name="baseFile">The image to use as the expression base.</param>
	/// <param name="position">The position.</param>
	/// <param name="zindex">The zindex.</param>
	CharacterObject(
		class IRenderer* renderer,
		const std::string& baseFile,
		Alignment position = Alignment::CENTER,
		int zindex = Config::values().zindexes.characters
	);
	
	/// <summary>
	/// Initializes a new instance of the <see cref="CharacterObject"/> class.
	/// </summary>
	/// <param name="renderer">The renderer.</param>
	/// <param name="baseFile">The image to use as the expression base.</param>
	/// <param name="position">The position.</param>
	/// <param name="zindex">The zindex.</param>
	CharacterObject(
		class IRenderer* renderer,
		const std::string& baseFile,
		Vector2<float> position,
		int zindex = Config::values().zindexes.characters
	);

	virtual ~CharacterObject();
	
	/// <summary>
	/// Draws this object to the specified renderer context.
	/// </summary>
	/// <param name="renderer">The renderer.</param>
	void draw(class IRenderer* renderer) override;
	
	/// <summary>
	/// Updates this instance.
	/// </summary>
	/// <param name="elapsedSeconds">The elapsed seconds.</param>
	void update(float elapsedSeconds) override;
	
	/// <summary>
	/// Sets the character position.
	/// </summary>
	/// <param name="position">The new position.</param>
	void setCharacterPosition(Alignment position);
	
	/// <summary>
	/// Starts a move transition with the specified interpolator.
	/// </summary>
	/// <param name="position">The position the object will move to.</param>
	/// <param name="time">The duration of the transition.</param>
	/// <param name="canBeSkipped">Whether or not this transition can be skipped by the player.</param>
	/// <param name="interpolator">The interpolator.</param>
	void moveToCharacterPosition(Alignment position, float time, bool canBeSkipped, class Interpolator* interpolator);
	
	/// <summary>
	/// Sets the expression of the character.
	/// </summary>
	/// <param name="expression">The expression.</param>
	void setExpression(const std::string& expression);
	
	/// <summary>
	/// Sets the path to the image to use as the expression base.
	/// </summary>
	/// <param name="expressionBase">The expression base.</param>
	void setExpressionBase(const std::string& expressionBase);
	
	/// <summary>
	/// Sets the image to use as a base. Exrpession base will remain unchanged.
	/// </summary>
	/// <param name="base">Path to the image that will be drawn as the base of the character sprite.</param>
	void setBase(const std::string& base);
	
	/// <summary>
	/// Sets the image to use as a base and the path to use as the expresion base.
	/// </summary>
	/// <param name="base">Path to the image that will be drawn as the base of the character sprite.</param>
	/// <param name="expressionBase">
	/// Path to the image to use as the expression base when constructing filenames for expression images.
	/// </param>
	void setBase(const std::string& base, const std::string& expressionBase);

	// Dissolve
	/// <summary>
	/// Change the expression of the character with a dissolve transition.
	/// </summary>
	/// <param name="expression">The new expression.</param>
	/// <param name="time">The duration of the transition.</param>
	/// <param name="canBeSkipped">Whether or not this transition can be skipped by the player.</param>
	void startDissolveExpression(const std::string& expression, float time, bool canBeSkipped);
		
	/// <summary>
	/// Change the expression and the base of the character with
	/// a dissolve transition.
	/// Expression base will remain unchanged
	/// </summary>
	/// <param name="base">Path to the image to draw as the new base.</param>
	/// <param name="expression">The new expression.</param>
	/// <param name="time">The duration of the transition.</param>
	/// <param name="canBeSkipped">Whether or not this transition can be skipped by the player.</param>
	void startDissolveBase(
		const std::string& base,
		const std::string& expression,
		float time,
		bool canBeSkipped
	);

	/// <summary>
	/// Change the expression and the base of the character with
	/// a dissolve transition.
	/// </summary>
	/// <param name="base">Path to the image to draw as the new base.</param>
	/// <param name="expressionBase">The path to the new expression base.</param>
	/// <param name="expression">The new expression.</param>
	/// <param name="time">The duration of the transition.</param>
	/// <param name="canBeSkipped">Whether or not this transition can be skipped by the player.</param>
	void startDissolveBase(
		const std::string& base,
		const std::string& expressionBase,
		const std::string& expression,
		float time,
		bool canBeSkipped
	);
	
	/// <summary>
	/// Enables color grading and sets the color LUT image to use.
	/// </summary>
	/// <param name="colorLUT">Path to the color LUT image.</param>
	/// <param name = "time">Duration in seconds of the lLUT transition.< / param>
	void setColorLut(const std::string& colorLUT, float time);
	
	/// <summary>
	/// Disables the color grading effect for this character.
	/// </summary>
	/// <param name = "colorLUT">Duration in seconds of the lLUT transition.< / param>
	void disableColorGrading(float time);

private:
	std::string basePath;
	std::string expressionBase;
	std::string expression;
	std::string fileExtension;
	const std::string& separator;
	bool sizeWasSet;

	// LUTs
	std::string colorLUT, previousColorLUT;
	bool colorGradingEnabled;
	bool blendLUTs;
	LinearInterpolator lutTransition;

	// Rendering
	class IRenderer* renderer;
	class ITexture* composedCharacter;
	class ITexture* dissolveEndResult;
	class ITexture* dissolveComposed;

	void setUp(const std::string& baseFile);
	void centerOrigin();
	void initializeSize(int w, int h);

	void drawCharacter(Rect<float>& rect, bool drawWithoutBlending, bool applyColorGrading = true);
	void drawExpression(const std::string& expression, Rect<float>& rect, Uint8 alpha);
	
	void drawIntermediateTexture(class ITexture* texture, bool applyColorGrading = true);
	Vector2<float> calculatePosition(Alignment position);
	void freeTransitionTextures();

	void setUpLutShader(class ColorGradingShader* colorGradingShader);
};