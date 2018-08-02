#pragma once

#include "Object.h"
#include <map>

/// <summary>
/// A class used to manage the <see cref="Object"/>s of the game.
/// It acts as a container of all the objects that are present
/// any given time, and is responsible for calling their update
/// and draw methods in the correct order.
/// </summary>
/// <seealso cref="Object" />
class GameObjectManager
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="GameObjectManager"/> class.
	/// </summary>
	GameObjectManager();
	~GameObjectManager();
	
	/// <summary>
	/// Adds the specified object to the container.
	/// </summary>
	/// <param name="object">The object to add.</param>
	void add(Object* object);

	/// <summary>
	/// Removes the specified object from the container.
	/// This will NOT delete the object.
	/// </summary>
	/// <param name="object">The object to remove.</param>
	/// <returns>
	/// <c>true</c> if the object was found and removed; otherwise, <c>false</c>.
	/// </returns>
	bool remove(Object* object);
	
	/// <summary>
	/// Updates all of the objects.
	/// </summary>
	void updateAll();
	
	/// <summary>
	/// Draws all of the objects in the correct order to the
	/// specified renderer context.
	/// </summary>
	/// <param name="renderer">The renderer.</param>
	void drawAll(class IRenderer* renderer) const;
	
	/// <summary>
	/// Sets the visibility of all of the objects to <c>false</c>.
	/// </summary>
	void hideAll();
	
	/// <summary>
	/// Removes and deallocates all of the objects.
	/// </summary>
	void clear();
	
	/// <summary>
	/// Starts counting down the specified number of seconds.
	/// If there was already a timer running, it will be replaced
	/// with the new one.
	/// </summary>
	/// <param name="seconds">The number of seconds.</param>
	void startTimer(float seconds);
	
	/// <summary>
	/// Checks if the timer has finished the countdown.
	/// </summary>
	/// <returns>
	/// <c>true</c> if the timer has reached zero seconds or
	/// there was no timer running; otherwise, <c>false</c>.
	/// </returns>
	bool timerFinished();
	
	/// <summary>
	/// Calculates the minimum elapsed time between frames
	/// based on the refresh rate of the display to compensate
	/// for v-sync issues when the game is in fullscreen mode.
	/// This only needs to be called once.
	/// </summary>
	void calculateMinimumElapsedTime();

private:
	// Object list
	std::multimap<int, Object*> objects;

	// Elapsed time
	Uint64 now, last;
	float minimumElapsedTime;

	// Timer
	float timer;

	void updateTimer(float elapsedSeconds);

	// Deallocator
	struct ObjectDeallocator
	{
		void operator()(const std::pair<int, Object*>& p) const
		{
			delete p.second;
		}
	};
};