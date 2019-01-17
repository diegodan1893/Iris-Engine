#pragma once

#include "LuaObject.h"

class LuaSprite : public LuaObject
{
public:
	LuaSprite(
		class GameObjectManager* gameObjectManager,
		class LuaEnvironment* lua,
		class SpriteObject* object
	);
	virtual ~LuaSprite();

	void defineSpriteSheet(int frameCount, int cols, int rows, int fps);
	void setFrame(int frame);
};