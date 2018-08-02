#pragma once

#include "WaitCommand.h"
#include <string>

/// <summary>
/// When evaluated, all of the objects will be
/// hidden except for the background, which will
/// be set to the specified image.
/// </summary>
/// <seealso cref="WaitCommand" />
class ClearScene : public WaitCommand
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="ClearScene"/> class.
	/// </summary>
	/// <param name="gameObjectManager">The game object manager.</param>
	/// <param name="background">The background object.</param>
	/// <param name="file">The path to the new background image.</param>
	/// <param name="enableMouseInput">Whether or not to enable mouse input after it's evaluated.</param>
	ClearScene(
		class GameObjectManager* gameObjectManager,
		class BackgroundObject* background,
		const std::string& file,
		bool enableMouseInput
	);
	
	/// <summary>
	/// Performs the operation (see <see cref="ClearScene"/>)
	/// and returns true.
	/// </summary>
	/// <returns><c>true</c>.</returns>
	bool ready() override;

private:
	class GameObjectManager* gameObjectManager;
	class BackgroundObject* background;
	std::string newBackground;
	bool enableMouseInput;
};