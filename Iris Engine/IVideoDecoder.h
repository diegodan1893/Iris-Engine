#pragma once

#include "Vector.h"
#include "IRenderer.h"

/// <summary>
/// A video decoder
/// </summary>
class IVideoDecoder
{
public:
	virtual ~IVideoDecoder() {}
	
	/// <summary>
	/// Starts decoding the video file.
	/// </summary>
	/// <param name="decodeAudio">if set to <c>true</c> audio will be decoded and played.</param>
	/// <param name="shouldLoop">if set to <c>true</c> the video will loop.</param>
	/// <returns>
	///   <c>true</c> if successful.
	/// </returns>
	virtual bool startDecoding(bool decodeAudio, bool shouldLoop) = 0;
	
	/// <summary>
	/// Stops the decoding of the video file.
	/// </summary>
	virtual void stopDecoding() = 0;
	
	/// <summary>
	/// Gets the size of the video.
	/// Decoding should be started before calling
	/// this function.
	/// </summary>
	/// <returns>The size of the video.</returns>
	virtual Vector2<int> getVideoSize() = 0;
	
	/// <summary>
	/// Gets the pixel format of the video.
	/// Decoding should be started before calling
	/// this function.
	/// </summary>
	/// <returns>The pixel format of the video.</returns>
	virtual TextureFormat getPixelFormat() = 0;
	
	/// <summary>
	/// Determines whether there is more video to play.
	/// </summary>
	/// <returns>
	///   <c>true</c> if there is more video to play; <c>false</c> if the video has ended.
	/// </returns>
	virtual bool hasVideo() = 0;
	
	/// <summary>
	/// Renders the next frame of the video to the
	/// provided texture and queues audio to be played.
	/// </summary>
	/// <param name="elapsedSeconds">The elapsed seconds.</param>
	/// <param name="texture">The texture.</param>
	virtual void getNextFrame(float elapsedSeconds, class ITexture* texture) = 0;
};