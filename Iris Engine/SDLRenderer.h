#pragma once

#include "IRenderer.h"

/// <summary>
/// A renderer context that uses
/// the SDL library.
/// Deprecated.
/// </summary>
/// <seealso cref="IRenderer" />
class SDLRenderer : public IRenderer
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="SDLRenderer"/> class.
	/// </summary>
	/// <param name="window">The window where rendering is displayed.</param>
	/// <param name="index">The index of the rendering driver to initialize.</param>
	/// <param name="flags">The flags.</param>
	SDLRenderer(struct SDL_Window* window, int index, uint32_t flags);
	~SDLRenderer();

	// Settings and properties	
	/// <summary>
	/// Determines whether this renderer was created
	/// correctly and can be used.
	/// </summary>
	/// <returns>
	/// <c>true</c> if there were no errors creating this renderer; otherwise, <c>false</c>.
	/// </returns>
	bool isValid() const override;

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

private:
	struct SDL_Renderer* renderer;
	bool valid;

	void copySDLRect(ITexture* texture, const struct SDL_Rect* srcrect, const struct SDL_Rect* dstrect);
};