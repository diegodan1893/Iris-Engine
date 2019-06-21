#include "VideoObject.h"
#include "IRenderer.h"
#include "ITexture.h"
#include "TheoraDecoder.h"
#include "Locator.h"
#include "Config.h"


VideoObject::VideoObject(IRenderer* renderer, const std::string& file, bool playAudio, bool shouldLoop, int zindex)
	:renderer(renderer),
	 playAudio(playAudio),
	 shouldLoop(shouldLoop),
	 playing(false),
	 decoder(nullptr),
	 videoTexture(nullptr),
	 Object(zindex)
{
	decoder = new TheoraVideoDecoder(Config::values().paths.videos + file);

	// Start buffering the video
	bool success = decoder->startDecoding(playAudio, shouldLoop);

	if (!success)
	{
		Locator::getLogger()->log(
			LogCategory::VIDEO,
			LogPriority::ERROR,
			u8"Could not play " + file
		);

		setValid(false);
	}
}

VideoObject::~VideoObject()
{
	if (decoder)
		delete decoder;

	if (videoTexture)
		delete videoTexture;
}

void VideoObject::draw(IRenderer* renderer)
{
	if (valid() && visible() && videoTexture)
	{
		videoTexture->setAlphaMod(getAlpha());
		renderer->copy(videoTexture, nullptr, &getRect());
	}
}

void VideoObject::update(float elapsedSeconds)
{
	if (playing)
	{
		if (!decoder->hasVideo())
		{
			// The video has ended
			stop();
		}
		else
		{
			// There is video to play
			// Decode it, but don't draw it if we are not going to render it
			decoder->getNextFrame(elapsedSeconds, (visible()) ? videoTexture : nullptr);
		}
	}

	// Update transitions
	if (inFade())
		updateAlpha(elapsedSeconds);

	if (inMovement())
		updateMovement(elapsedSeconds);
}


void VideoObject::play()
{
	if (!playing && valid())
	{
		if (!decoder->hasVideo())
			decoder->startDecoding(playAudio, shouldLoop);

		playing = true;

		if (!videoTexture)
		{
			// We need to create a texture for the video
			Vector2<int> size = decoder->getVideoSize();
			setSize(size.x, size.y);
			TextureFormat format = decoder->getPixelFormat();

			videoTexture = renderer->createTexture(format, TextureAccess::STREAMING, size.x, size.y);
			videoTexture->setBlendMode(BlendMode::BLEND);
		}
	}
}

void VideoObject::stop()
{
	if (playing)
	{
		decoder->stopDecoding();
		playing = false;
		setVisible(false);
	}
}

bool VideoObject::isPlaying()
{
	return playing;
}
