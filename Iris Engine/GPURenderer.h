#pragma once

#include "IRenderer.h"
#include "TestShader.h"
#include "DissolveShader.h"
#include "ImageDissolveShader.h"

/// <summary>
/// A renderer context that uses
/// the SDL_gpu library.
/// </summary>
/// <seealso cref="IRenderer" />
class GPURenderer : public IRenderer
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="GPURenderer"/> class.
	/// </summary>
	/// <param name="window">The window where the game will be drawn.</param>
	GPURenderer(struct SDL_Window* window);
	~GPURenderer();

	// Settings and properties	
	/// <summary>
	/// Determines whether this renderer was created
	/// correctly and can be used.
	/// </summary>
	/// <returns>
	///   <c>true</c> if there were no errors creating this renderer; otherwise, <c>false</c>.
	/// </returns>
	bool isValid() const override;
	
	/// <summary>
	/// Checks if fullscreen mode is active.
	/// </summary>
	/// <returns>
	///   <c>true</c> if the game is in fullscreen mode; otherwise, <c>false</c>.
	/// </returns>
	bool getFullscreen() override;
	
	/// <summary>
	/// Enables or disables fullscreen mode.
	/// The game will be rendered using a virtual
	/// resolution. The final image will be scaled
	/// to fit the actual size of the screen.
	/// </summary>
	/// <param name="fullscreen">if set to <c>true</c> fullscreen mode will be enabled.</param>
	/// <param name="virtualW">The width of the logical resolution.</param>
	/// <param name="virtualH">The height of the logical resolution.</param>
	void setFullScreen(bool fullscreen) override;
	
	/// <summary>
	/// Gets the resolution of the window.
	/// </summary>
	/// <returns></returns>
	Vector2<int> getWindowResolution() override;

	// Rendering	
	/// <summary>
	/// Clears the render target.
	/// </summary>
	void clear() override;
	
	/// <summary>
	/// Updates the screen with any rendering
	/// performed since the previous call.
	/// </summary>
	void present() override;
	
	/// <summary>
	/// Sets a texture as the current rendering
	/// target.
	/// </summary>
	/// <param name="texture">The targeted texture, or nullptr for the screen.</param>
	void setRenderTarget(ITexture* texture) override;
	
	/// <summary>
	/// Copies a portion of a texture to the
	/// current rendering target.
	/// </summary>
	/// <param name="texture">The source texture.</param>
	/// <param name="srcrect">The portion of the texture to copy.</param>
	/// <param name="dstrect">The portion of the target where the source texture will be drawn.</param>
	void copy(ITexture* texture, const Rect<float>* srcrect, const Rect<float>* dstrect) override;

	// Textures	
	/// <summary>
	/// Creates a blank texture that
	/// can be used in this rendering context.
	/// </summary>
	/// <param name="format">The format of the texture.</param>
	/// <param name="access">The access mode of the texture.</param>
	/// <param name="w">The width of the texture.</param>
	/// <param name="h">The height of the texture.</param>
	/// <returns>
	/// A pointer to the new texture
	/// </returns>
	ITexture* createTexture(TextureFormat format, TextureAccess access, int w, int h) override;
	
	/// <summary>
	/// Creates a texture from a SDL_Surface
	/// that can be used in this rendering
	/// context.
	/// </summary>
	/// <param name="surface">The surface.</param>
	/// <returns>
	/// A pointer to the new texture
	/// </returns>
	ITexture* createTexture(struct SDL_Surface* surface) override;

	// Shaders
	TestShader* getTestShader() override;
	DissolveShader* getDissolveShader() override;
	ImageDissolveShader* getImageDissolveShader() override;

private:
	// Targets
	struct GPU_Target* screen;
	struct GPU_Target* windowTarget;
	struct GPU_Target* currentTarget;

	// Buffers
	class GPUTexture* virtualScreen;

	// Fullscreen scaling values
	float scalingFactor;
	Vector2<float> screenPosition;

	// Properties
	bool valid;

	// Shaders
	TestShader testShader;
	DissolveShader dissolveShader;
	ImageDissolveShader imageDissolveShader;
};