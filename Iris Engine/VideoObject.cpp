#include "VideoObject.h"
#include "IRenderer.h"
#include "ITexture.h"
#include "TheoraDecoder.h"
#include "Locator.h"
#include "Sprite.h"

VideoObject::VideoObject(IRenderer* renderer, const std::string& file, bool playAudio, int zindex)
	:renderer(renderer),
	 file(file),
	 playAudio(playAudio),
	 playing(false),
	 decoder(nullptr),
	 videoTexture(nullptr),
	 Object(zindex)
{
	decoder = new TheoraDecoder(file);

	// Start buffering the video
	bool success = decoder->startDecoding(playAudio);

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
			if (shouldLoop)
				decoder->rewind();
			else
				stop();
		}
		else
		{
			// There is video to play
			decoder->getNextFrame(videoTexture);
		}
	}

	// Update transitions
	if (inFade())
		updateAlpha(elapsedSeconds);

	if (inMovement())
		updateMovement(elapsedSeconds);
}

void VideoObject::play(bool loop)
{
	if (!playing && valid())
	{
		shouldLoop = loop;
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
	decoder->stopDecoding();
	playing = false;
	setVisible(false);
}

bool VideoObject::isPlaying()
{
	return playing;
}
