#include "TheoraDecoder.h"
#include "theoraplay.h"
#include "Locator.h"
#include "ITexture.h"
#include <SDL.h>

TheoraVideoDecoder::TheoraVideoDecoder(const std::string& file)
	:file(file),
	 video(nullptr),
	 initialized(false)
{
}

TheoraVideoDecoder::~TheoraVideoDecoder()
{
	stopDecoding();
}

bool TheoraVideoDecoder::startDecoding(bool decodeAudio, bool shouldLoop)
{
	const int MAX_FRAMES = 45;

	this->decodeAudio = decodeAudio;
	decoder = THEORAPLAY_startDecodeFile(file.c_str(), MAX_FRAMES, THEORAPLAY_VIDFMT_RGB, shouldLoop);

	if (decoder)
		return true;
	else
		return false;
}

void TheoraVideoDecoder::stopDecoding()
{
	if (video)
	{
		THEORAPLAY_freeVideo(video);
		video = nullptr;
	}

	if (decoder)
	{
		THEORAPLAY_stopDecode(decoder);
		decoder = nullptr;
	}

	if (decodeAudio)
	{
		Locator::getAudio()->hookMusicPlayer(nullptr, nullptr);
	}

	while (!audioQueue.empty())
	{
		THEORAPLAY_freeAudio(audioQueue.front().audio);
		audioQueue.pop();
	}

	initialized = false;
}

Vector2<int> TheoraVideoDecoder::getVideoSize()
{
	if (!initialized)
		initialize();

	return size;
}

TextureFormat TheoraVideoDecoder::getPixelFormat()
{
	return TextureFormat::RGB;
}

bool TheoraVideoDecoder::hasVideo()
{
	return decoder && THEORAPLAY_isDecoding(decoder);
}

void TheoraVideoDecoder::getNextFrame(float elapsedSeconds, ITexture* texture)
{
	const int MAX_AUDIO_DELAY_FRAMES = 5;

	if (!initialized)
		initialize();

	playtime += elapsedSeconds;
	uint32_t now = std::round(playtime * 1000.0f) + frameMS;

	// Queue audio
	const THEORAPLAY_AudioPacket* audio;
	bool keepDecoding = true;

	while (keepDecoding && (audio = THEORAPLAY_getAudio(decoder)) != nullptr)
	{
		// Don't spend all of the CPU budget decoding audio
		if (audio->playms > now + 2000)
			keepDecoding = false;

		// We have audio to decode
		if (decodeAudio && audio->playms > (double)now - frameMS * MAX_AUDIO_DELAY_FRAMES)
			queueAudio(audio);
		else
			THEORAPLAY_freeAudio(audio);
	}

	// Decode next frame of video
	if (decodeVideo)
	{
		if (!video)
			video = THEORAPLAY_getVideo(decoder);

		// Play next frame if it's time to do so
		if (video && video->playms <= now)
		{
			if (frameMS && now - video->playms >= frameMS)
			{
				// We need to skip frames to catch up
				const THEORAPLAY_VideoFrame* last = video;
				bool stopSkipping = false;

				while (!stopSkipping && (video = THEORAPLAY_getVideo(decoder)) != nullptr)
				{
					THEORAPLAY_freeVideo(last);
					last = video;

					if (now - video->playms < frameMS || video->playms > now)
						stopSkipping = true;
				}

				if (!video)
				{
					video = last;

					// We skipped all frames and still didn't catch up
					// Panic! This will cause audio desync
					Locator::getLogger()->log(
						LogCategory::VIDEO,
						LogPriority::INFO,
						u8"Can't keep up with video playback."
					);

					if (decodeAudio)
					{
						// Rewind the video so that it syncs with audio playback
						playtime = audioPlayMS / 1000.0f;
					}
				}
			}

			// Draw the frame
			if (texture)
				texture->updateTextureBytes(video->pixels);

			// Free frame
			THEORAPLAY_freeVideo(video);
			video = nullptr;
		}
	}
}

void TheoraVideoDecoder::initialize()
{
	// Wait until the decoder has parsed out video properties
	while (!THEORAPLAY_isInitialized(decoder))
		SDL_Delay(10);

	decodeAudio = decodeAudio && THEORAPLAY_hasAudioStream(decoder);
	decodeVideo = THEORAPLAY_hasVideoStream(decoder) != 0;

	if (decodeVideo)
	{
		// Get the first frame of video to get the properties
		while ((video = THEORAPLAY_getVideo(decoder)) == nullptr)
			SDL_Delay(10);

		size.x = video->width;
		size.y = video->height;

		frameMS = (video->fps == 0.0) ? 0 : ((uint32_t)(1000.0f / video->fps));
	}
	else
	{
		size.x = size.y = 0;
	}

	if (decodeAudio)
	{
		AudioFormat format = Locator::getAudio()->getAudioFormat();

		if (format == AudioFormat::S16LSB || format == AudioFormat::S16MSB)
		{
			// Hook music player
			Locator::getAudio()->hookMusicPlayer(&musicPlayer, this);
		}
		else
		{
			// Unsupported audio format
			decodeAudio = false;
			Locator::getLogger()->log(
				LogCategory::AUDIO,
				LogPriority::ERROR,
				u8"Your system has an unsupported audio format for decoding audio from videos."
			);
		}
	}

	initialized = true;

	playtime = 0;
	audioPlayMS = 0;
}

void TheoraVideoDecoder::musicPlayer(void* udata, uint8_t* stream, int len)
{
	((TheoraVideoDecoder*)udata)->playAudio(stream, len);
}

void TheoraVideoDecoder::playAudio(uint8_t* stream, int len)
{
	const Sint16 SINT_MIN = -32768;
	const Sint16 SINT_MAX = 32767;
	const float CONVERSION_FACTOR = 32767.0f;

	Sint16* dst = (Sint16*)stream;

	audioLock.lock();
	while (!audioQueue.empty() && len > 0)
	{
		// Get next item in the queue
		AudioItem& item = audioQueue.front();

		int channels = item.audio->channels;

		const float* src = item.audio->samples + (item.offset * channels);
		int cpy = (item.audio->frames - item.offset) * channels;

		// Copy only the bytes that will fit in the buffer
		if (cpy > len / sizeof(Sint16))
			cpy = len / sizeof(Sint16);

		// Copy bytes
		for (int i = 0; i < cpy; ++i)
		{
			float val = *(src++);

			// Format conversion
			if (val < -1.0f)
				*(dst++) = SINT_MIN;
			else if (val > 1.0f)
				*(dst++) = SINT_MAX;
			else
				*(dst++) = (Sint16)(val * CONVERSION_FACTOR);
		}

		item.offset += cpy / channels;
		len -= cpy * sizeof(Sint16);

		// If there is no more data to copy from this sample, free it
		if (item.offset >= item.audio->frames)
		{
			audioPlayMS = item.audio->playms;
			THEORAPLAY_freeAudio(item.audio);
			audioQueue.pop();
		}
	}
	audioLock.unlock();

	// Fill the rest of the buffer with silence
	if (len > 0)
		memset(dst, '\0', len);
}

void TheoraVideoDecoder::queueAudio(const THEORAPLAY_AudioPacket* audio)
{
	AudioItem item;

	item.audio = audio;
	item.offset = 0;

	audioLock.lock();
	audioQueue.push(item);
	audioLock.unlock();
}
