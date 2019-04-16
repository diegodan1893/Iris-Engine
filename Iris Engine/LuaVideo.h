#pragma once

#include "LuaObject.h"

class LuaVideo : public LuaObject
{
public:
	LuaVideo(
		class GameObjectManager* gameObjectManager,
		class LuaEnvironment* lua,
		class VideoObject* object
	);
	virtual ~LuaVideo();

	void play(bool loop, bool shouldBlock, sol::this_state s);
	void stop();
	void waitUntilFinished(sol::this_state s);
};