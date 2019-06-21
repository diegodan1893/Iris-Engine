#pragma once

#include "IAudio.h"
#include <SDL_mixer.h>
#include <vector>

/// <summary>
/// Audio service implemented using SDL_mixer.
/// </summary>
/// <seealso cref="IAudio" />
class MixAudio : public IAudio
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="MixAudio"/> class.
	/// </summary>
	/// <param name="audioChannels">The number of audio channels.</param>
	MixAudio(int audioChannels);
	~MixAudio();

	// Music	
	/// <summary>
	/// Loads and plays a song.
	/// </summary>
	/// <param name="filename">The audio file to play.</param>
	virtual void playMusic(const std::string& filename) override;
	
	/// <summary>
	/// Loads and fades in a song.
	/// </summary>
	/// <param name="filename">The audio file to play.</param>
	/// <param name="seconds">The duration of the fade in seconds.</param>
	virtual void fadeInMusic(const std::string& filename, float seconds) override;
	
	/// <summary>
	/// Stops the music.
	/// </summary>
	virtual void stopMusic() override;
	
	/// <summary>
	/// Stops the music with a fade.
	/// </summary>
	/// <param name="seconds">The duration of the fade in seconds.</param>
	virtual void fadeOutMusic(float seconds) override;
	
	/// <summary>
	/// Sets up a custom music player function.
	/// The function will be called with arg passed into the udata parameter.
	/// The stream parameter passes in the audio stream buffer to be filled
	/// with len bytes of music.
	/// To return to the usual music player, call this function with nullptr
	/// on both parameters.
	/// DO NOT call audio functions from the callback function.
	/// </summary>
	/// <param name="musicPlayer">The custom music player function.</param>
	/// <param name="arg">The argument to be passed to the udata parameter when the callback function is called.</param>
	virtual void hookMusicPlayer(void(*musicPlayer)(void* udata, uint8_t* stream, int len), void* arg) override;

	// Sounds	
	/// <summary>
	/// Plays a cached sound.
	/// </summary>
	/// <param name="filename">The audio file to play.</param>
	virtual void playSound(const std::string& filename) override;
	
	/// <summary>
	/// Stops a sound.
	/// </summary>
	/// <param name="filename">The name of the audio file used to load the sound.</param>
	virtual void stopSound(const std::string& filename) override;
	
	/// <summary>
	/// Gets the audio format.
	/// </summary>
	/// <returns>
	/// The audio format.
	/// </returns>
	virtual AudioFormat getAudioFormat() override;

private:
	Mix_Music* music;
	std::vector<std::string> sounds;
	int nextChannel;

	void stopAndFreeMusic();
	void logMixError(const std::string& error);
};