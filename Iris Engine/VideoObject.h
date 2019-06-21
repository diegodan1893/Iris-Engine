#pragma once

#include "Object.h"
#include <string>

/// <summary>
/// An object that can play a video file
/// </summary>
/// <seealso cref="Object" />
class VideoObject : public Object
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="VideoObject" /> class.
	/// </summary>
	/// <param name="renderer">The renderer.</param>
	/// <param name="file">The file containing the video.</param>
	/// <param name="playAudio">if set to <c>true</c> the audio of the video will be played.</param>
	/// <param name="shouldLoop">if set to <c>true</c> the video will loop.</param>
	/// <param name="zindex">The zindex.</param>
	VideoObject(
		class IRenderer* renderer,
		const std::string& file,
		bool playAudio,
		bool shouldLoop,
		int zindex
	);

	virtual ~VideoObject();
	
	/// <summary>
	/// Draws this object to the specified renderer context.
	/// </summary>
	/// <param name="renderer">The renderer.</param>
	virtual void draw(class IRenderer* renderer) override;
	
	/// <summary>
	/// Updates this instance.
	/// </summary>
	/// <param name="elapsedSeconds">The elapsed seconds since the last call to this method.</param>
	virtual void update(float elapsedSeconds) override;
	
	/// <summary>
	/// Starts playing the video.
	/// </summary>
	void play();
	
	/// <summary>
	/// Stops playing the video.
	/// </summary>
	void stop();
	
	/// <summary>
	/// Determines whether the video is playing.
	/// </summary>
	/// <returns>
	///   <c>true</c> if the video is playing; otherwise, <c>false</c>.
	/// </returns>
	bool isPlaying();

private:
	// Video
	bool playAudio;
	bool shouldLoop;
	bool playing;
	class IVideoDecoder* decoder;

	// Rendering
	class IRenderer* renderer;
	class ITexture* videoTexture;
};