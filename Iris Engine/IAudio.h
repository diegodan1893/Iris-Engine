#pragma once

#include <string>

/// <summary>
/// Audio service.
/// </summary>
class IAudio
{
public:
	virtual ~IAudio() {}

	// Music	
	/// <summary>
	/// Loads and plays a song.
	/// </summary>
	/// <param name="filename">The audio file to play.</param>
	virtual void playMusic(const std::string& filename) = 0;
	
	/// <summary>
	/// Loads and fades in a song.
	/// </summary>
	/// <param name="filename">The audio file to play.</param>
	/// <param name="seconds">The duration of the fade in seconds.</param>
	virtual void fadeInMusic(const std::string& filename, float seconds) = 0;
	
	/// <summary>
	/// Stops the music.
	/// </summary>
	virtual void stopMusic() = 0;
	
	/// <summary>
	/// Stops the music with a fade.
	/// </summary>
	/// <param name="seconds">The duration of the fade in seconds.</param>
	virtual void fadeOutMusic(float seconds) = 0;

	// Sounds	
	/// <summary>
	/// Plays a cached sound.
	/// </summary>
	/// <param name="filename">The audio file to play.</param>
	virtual void playSound(const std::string& filename) = 0;
	
	/// <summary>
	/// Stops a sound.
	/// </summary>
	/// <param name="filename">The name of the audio file used to load the sound.</param>
	virtual void stopSound(const std::string& filename) = 0;
};