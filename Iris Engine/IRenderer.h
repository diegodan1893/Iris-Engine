#pragma once

#include "Vector.h"
#include <cstdint>
#include <string>

/// <summary>
/// Supported texture formats.
/// </summary>
enum class TextureFormat
{
	RGB,
	RGBA8
};

/// <summary>
/// Supported texture access modes.
/// </summary>
enum class TextureAccess
{
	STATIC,
	STREAMING,
	TARGET
};

class ITexture;

/// <summary>
/// A renderer context.
/// </summary>
class IRenderer
{
public:
	virtual ~IRenderer() {}

	// Settings and properties	
	/// <summary>
	/// Determines whether this renderer was created
	/// correctly and can be used.
	/// </summary>
	/// <returns>
	/// <c>true</c> if there were no errors creating this renderer; otherwise, <c>false</c>.
	/// </returns>
	virtual bool isValid() const = 0;
	
	/// <summary>
	/// Checks if fullscreen mode is active.
	/// </summary>
	/// <returns>
	/// <c>true</c> if the game is in fullscreen mode; otherwise, <c>false</c>.
	/// </returns>
	virtual bool getFullscreen() = 0;
	
	/// <summary>
	/// Enables or disables fullscreen mode.
	/// The game will be rendered using a virtual
	/// resolution. The final image will be scaled
	/// to fit the actual size of the screen.
	/// </summary>
	/// <param name="fullscreen">if set to <c>true</c> fullscreen mode will be enabled.</param>
	virtual void setFullScreen(bool fullscreen) = 0;
	
	/// <summary>
	/// Gets the scaling factor of the game.
	/// 1.0 if the game is being rendered at native resolution.
	/// </summary>
	/// <returns>The scaling factor.</returns>
	virtual float getScalingFactor() = 0;
	
	/// <summary>
	/// Gets the offset of the game image caused
	/// by letterboxing in fullscreen.
	/// </summary>
	/// <returns></returns>
	virtual Vector2<int> getLetterboxingOffset() = 0;
	
	/// <summary>
	/// Gets the resolution of the window.
	/// </summary>
	/// <returns></returns>
	virtual Vector2<int> getWindowResolution() = 0;

	// Rendering	
	/// <summary>
	/// Clears the render target.
	/// </summary>
	virtual void clear() = 0;
	
	/// <summary>
	/// Updates the screen with any rendering
	/// performed since the previous call.
	/// </summary>
	virtual void present() = 0;
	
	/// <summary>
	/// Sets a texture as the current rendering
	/// target.
	/// </summary>
	/// <param name="texture">The targeted texture, or nullptr for the screen.</param>
	virtual void setRenderTarget(ITexture* texture) = 0;
	
	/// <summary>
	/// Copies a portion of a texture to the
	/// current rendering target.
	/// </summary>
	/// <param name="texture">The source texture.</param>
	/// <param name="srcrect">The portion of the texture to copy.</param>
	/// <param name="dstrect">The portion of the target where the source texture will be drawn.</param>
	virtual void copy(
		ITexture* texture,
		const Rect<float>* srcrect,
		const Rect<float>* dstrect
	) = 0;

	// Textures	
	/// <summary>
	/// Creates a blank texture that
	/// can be used in this rendering context.
	/// </summary>
	/// <param name="format">The format of the texture.</param>
	/// <param name="access">The access mode of the texture.</param>
	/// <param name="w">The width of the texture.</param>
	/// <param name="h">The height of the texture.</param>
	/// <returns>A pointer to the new texture</returns>
	virtual ITexture* createTexture(TextureFormat format, TextureAccess access, int w, int h) = 0;
	
	/// <summary>
	/// Creates a texture from a SDL_Surface
	/// that can be used in this rendering
	/// context.
	/// </summary>
	/// <param name="surface">The surface.</param>
	/// <returns>A pointer to the new texture</returns>
	virtual ITexture* createTexture(struct SDL_Surface* surface) = 0;
	
	/// <summary>
	/// Captures a screenshot of the game and saves
	/// it to a file.
	/// The image is stretched to fit the provided
	/// resolution.
	/// </summary>
	/// <param name="path">The path where you want to save the screenshot.</param>
	/// <param name="w">The width of the final image in pixels.</param>
	/// <param name="h">The height of the final image in pixels.</param>
	virtual void saveScreenshot(const std::string& path, int w, int h) = 0;

	// Shaders
	virtual class TestShader* getTestShader() = 0;
	virtual class DissolveShader* getDissolveShader() = 0;
	virtual class ImageDissolveShader* getImageDissolveShader() = 0;
	virtual class ColorGradingShader* getColorGradingShader() = 0;
};