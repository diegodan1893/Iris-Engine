#pragma once

#include "IVideoDecoder.h"
#include <string>
#include <mutex>
#include <queue>

/// <summary>
/// 
/// </summary>
/// <seealso cref="IVideoDecoder" />
class TheoraDecoder : public IVideoDecoder
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="TheoraDecoder"/> class.
	/// </summary>
	/// <param name="file">Path to the video file.</param>
	TheoraDecoder(const std::string& file);

	~TheoraDecoder();
	
	/// <summary>
	/// Starts decoding the video file.
	/// </summary>
	/// <param name="decodeAudio">if set to <c>true</c> audio will be decoded and played.</param>
	/// <returns>
	///   <c>true</c> if successful.
	/// </returns>
	bool startDecoding(bool decodeAudio) override;
	
	/// <summary>
	/// Stops the decoding of the video file.
	/// </summary>
	void stopDecoding() override;

	/// <summary>
	/// Gets the size of the video.
	/// Decoding should be started before calling
	/// this function.
	/// </summary>
	/// <returns>The size of the video.</returns>
	Vector2<int> getVideoSize() override;
	
	/// <summary>
	/// Gets the pixel format of the video.
	/// Decoding should be started before calling
	/// this function.
	/// </summary>
	/// <returns>
	/// The pixel format of the video.
	/// </returns>
	TextureFormat getPixelFormat() override;
	
	/// <summary>
	/// Determines whether there is more video to play.
	/// </summary>
	/// <returns>
	///   <c>true</c> if there is more video to play; <c>false</c> if the video has ended.
	/// </returns>
	bool hasVideo() override;
	
	/// <summary>
	/// Seeks to the beginning of the video and
	/// starts decoding from there.
	/// </summary>
	void rewind() override;
	
	/// <summary>
	/// Renders the next frame of the video to the
	/// provided texture and queues audio to be played.
	/// </summary>
	/// <param name="texture">The texture.</param>
	void getNextFrame(class ITexture* texture) override;

private:
	// Video properties
	std::string file;
	bool decodeAudio;
	bool decodeVideo;
	Vector2<int> size;
	uint32_t frameMS;

	// Decoder
	struct THEORAPLAY_Decoder* decoder;
	const struct THEORAPLAY_VideoFrame* video;
	bool initialized;
	uint32_t baseTicks;

	// Audio
	struct AudioItem
	{
		const struct THEORAPLAY_AudioPacket* audio;
		int offset;
	};

	std::mutex audioLock;
	std::queue<AudioItem> audioQueue;
	uint16_t audioPlayMS;

	// Initialization
	void initialize();

	// Music player
	static void musicPlayer(void* udata, uint8_t* stream, int len);
	void playAudio(uint8_t* stream, int len);
	void queueAudio(const struct THEORAPLAY_AudioPacket* audio);
};