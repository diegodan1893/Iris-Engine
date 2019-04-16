#include "MixAudio.h"
#include "Locator.h"
#include "Sound.h"

MixAudio::MixAudio(int audioChannels)
	:music(nullptr),
	 nextChannel(0)
{
	sounds.resize(audioChannels);
}

MixAudio::~MixAudio()
{
	stopAndFreeMusic();
}

void MixAudio::playMusic(const std::string& filename)
{
	stopAndFreeMusic();

	music = Mix_LoadMUS(filename.c_str());

	if (music)
	{
		if (Mix_PlayMusic(music, -1))
			logMixError(u8"Music could not be played");
	}
	else
	{
		logMixError(u8"Music could not be loaded");
	}
}

void MixAudio::fadeInMusic(const std::string& filename, float seconds)
{
	stopAndFreeMusic();

	music = Mix_LoadMUS(filename.c_str());

	if (music)
	{
		if (Mix_FadeInMusic(music, -1, (int)(seconds * 1000)))
			logMixError(u8"Music could not be played");
	}
	else
	{
		logMixError(u8"Music could not be loaded");
	}
}

void MixAudio::stopMusic()
{
	Mix_HaltMusic();
}

void MixAudio::fadeOutMusic(float seconds)
{
	Mix_FadeOutMusic((int)(seconds * 1000));
}

void MixAudio::hookMusicPlayer(void(*musicPlayer)(void* udata, uint8_t* stream, int len), void* arg)
{
	Mix_HookMusic(musicPlayer, arg);
}

void MixAudio::playSound(const std::string& filename)
{
	Sound* sound = Locator::getCache()->getSound(filename);

	if (sound)
	{
		Mix_Chunk* chunk = sound->getChunk();

		if (chunk)
		{
			Mix_HaltChannel(nextChannel);

			if (Mix_PlayChannel(nextChannel, chunk, 0) == -1)
			{
				logMixError(u8"Sound could not be played");
			}
			else
			{
				sounds[nextChannel] = filename;
			}

			nextChannel = (nextChannel + 1) % sounds.size();
		}
	}
}

void MixAudio::stopSound(const std::string& filename)
{
	// Halt all channels where the sound is being played
	int channel;

	for (int i = 0; i < sounds.size(); ++i)
	{
		if (sounds[i] == filename)
		{
			channel = i;
			Mix_HaltChannel(channel);
		}
	}
}

AudioFormat MixAudio::getAudioFormat()
{
	int frequency;
	uint16_t format;
	int channels;

	Mix_QuerySpec(&frequency, &format, &channels);

	AudioFormat audioFormat;

	switch (format)
	{
	case AUDIO_U8:
		audioFormat = AudioFormat::U8;
		break;

	case AUDIO_S8:
		audioFormat = AudioFormat::S8;
		break;

	case AUDIO_U16LSB:
		audioFormat = AudioFormat::U16LSB;
		break;

	case AUDIO_S16LSB:
		audioFormat = AudioFormat::S16LSB;
		break;

	case AUDIO_U16MSB:
		audioFormat = AudioFormat::U16MSB;
		break;

	case AUDIO_S16MSB:
		audioFormat = AudioFormat::S16MSB;
		break;

	default:
		audioFormat = AudioFormat::UNKNOWN;
		break;
	}

	return audioFormat;
}

void MixAudio::stopAndFreeMusic()
{
	stopMusic();

	if (music)
		Mix_FreeMusic(music);
}

void MixAudio::logMixError(const std::string& error)
{
	Locator::getLogger()->log(
		LogCategory::AUDIO,
		LogPriority::ERROR,
		error + u8":\n" + std::string(Mix_GetError())
	);
}
