#include "LuaVideo.h"
#include "VideoObject.h"
#include "LuaEnvironment.h"
#include "WaitForVideo.h"

LuaVideo::LuaVideo(GameObjectManager* gameObjectManager, LuaEnvironment* lua, VideoObject* object)
	:LuaObject(gameObjectManager, lua, object)
{
}

LuaVideo::~LuaVideo()
{
}

void LuaVideo::play(bool loop, bool shouldBlock, sol::this_state s)
{
	VideoObject* video = (VideoObject*)getObject();
	video->play(loop);

	if (shouldBlock)
	{
		getLua()->waitFor(new WaitForVideo(video));
		lua_yield(s, 0);
	}
}

void LuaVideo::stop()
{
	((VideoObject*)getObject())->stop();
}

void LuaVideo::waitUntilFinished(sol::this_state s)
{
	getLua()->waitFor(new WaitForVideo((VideoObject*)getObject()));
	lua_yield(s, 0);
}
