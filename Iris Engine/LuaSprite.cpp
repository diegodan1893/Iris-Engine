#include "LuaSprite.h"
#include "Locator.h"
#include "SpriteObject.h"

LuaSprite::LuaSprite(GameObjectManager* gameObjectManager, LuaEnvironment* lua, SpriteObject* object)
	:LuaObject(gameObjectManager, lua, object)
{
}

LuaSprite::~LuaSprite()
{
}

void LuaSprite::defineSpriteSheet(int frameCount, int cols, int rows, int fps)
{
	getObject()->defineSpriteSheet(frameCount, cols, rows, fps);
}

void LuaSprite::setFrame(int frame)
{
	if (getObject()->isAnimatedSprite() && frame >= 0 && frame < getObject()->getFrameCount())
	{
		getObject()->setFrame(frame);
	}
	else
	{
		Locator::getLogger()->log(
			LogCategory::LUA,
			LogPriority::ERROR,
			u8"Trying to set an invalid frame number"
		);
	}
}