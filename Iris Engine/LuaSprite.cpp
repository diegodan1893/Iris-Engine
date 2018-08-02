#include "LuaSprite.h"
#include "SpriteObject.h"
#include "ButtonObject.h"
#include "GameObjectManager.h"
#include "WaitQueue.h"
#include "WaitForTransition.h"
#include "Locator.h"
#include "TransitionUtils.h"
#include "LuaEnvironment.h"

LuaSprite::LuaSprite(GameObjectManager* gom, LuaEnvironment* lua, SpriteObject* object)
	:gameObjectManager(gom),
	 lua(lua),
	 object(object)
{
	// Add sprite to game object manager
	gameObjectManager->add(object);
}

LuaSprite::~LuaSprite()
{
	// Remove object from game object manager and delete it
	bool success = gameObjectManager->remove(object);

	if (success)
		delete object;
	
	// Can't log because logger may not exist at this point
}

void LuaSprite::show()
{
	// By default, sprites show with a non-blocking 0.3 seconds fade
	object->startFadeIn(0.3f, false);
}

void LuaSprite::showTransition(const sol::table& transition, sol::this_state s)
{
	TransitionType transitionType;

	if (TransitionUtils::getTransitionType(transition, transitionType))
	{
		switch (transitionType)
		{
		case TransitionType::NONE:
			object->setVisible(true);
			break;

		case TransitionType::FADE:
			float transitionTime;
			bool shouldBlock;

			if (TransitionUtils::getTransitionTime(transition, transitionTime) &&
				TransitionUtils::getTransitionBlocking(transition, shouldBlock))
			{
				object->startFadeIn(transitionTime, shouldBlock);

				if (shouldBlock)
				{
					lua->waitFor(new WaitForTransition(object));
					lua_yield(s, 0);
				}
			}

			break;

		default:
			Locator::getLogger()->log(
				LogCategory::LUA,
				LogPriority::ERROR,
				u8"Invalid transition type for method 'hide' of CharacterSprite"
			);

			break;
		}
	}
}

void LuaSprite::hide()
{
	// By default, sprites hide with a non-blocking 0.3 seconds fade
	object->startFadeOut(0.3f, false);
}

void LuaSprite::hideTransition(const sol::table & transition, sol::this_state s)
{
	TransitionType transitionType;

	if (TransitionUtils::getTransitionType(transition, transitionType))
	{
		switch (transitionType)
		{
		case TransitionType::NONE:
			object->setVisible(false);
			break;

		case TransitionType::FADE:
			float transitionTime;
			bool shouldBlock;

			if (TransitionUtils::getTransitionTime(transition, transitionTime) &&
				TransitionUtils::getTransitionBlocking(transition, shouldBlock))
			{
				object->startFadeOut(transitionTime, shouldBlock);

				if (shouldBlock)
				{
					lua->waitFor(new WaitForTransition(object));
					lua_yield(s, 0);
				}
			}

			break;

		default:
			Locator::getLogger()->log(
				LogCategory::LUA,
				LogPriority::ERROR,
				u8"Invalid transition type for method 'hide' of CharacterSprite"
			);

			break;
		}
	}
}

void LuaSprite::skipTransition()
{
	object->skipTransition();
}

void LuaSprite::setPosition(float x, float y)
{
	object->skipMovement();
	object->setPosition(x, y);
}

std::tuple<float, float> LuaSprite::getPosition()
{
	Vector2<float> position = object->getPosition();
	return std::make_tuple(position.x, position.y);
}

void LuaSprite::setOrigin(int x, int y)
{
	object->setOrigin(x, y);
}

void LuaSprite::move(float x, float y, float time, bool shouldBlock, sol::this_state s)
{
	moveInterpolator(x, y, time, shouldBlock, InterpolatorType::DEFAULT, s);
}

void LuaSprite::moveInterpolator(
	float x,
	float y,
	float time,
	bool shouldBlock,
	InterpolatorType interpolator,
	sol::this_state s
)
{
	object->move(x, y, time, shouldBlock, TransitionUtils::getInterpolator(interpolator));

	if (shouldBlock)
	{
		lua->waitFor(new WaitForTransition(object));
		lua_yield(s, 0);
	}
}

void LuaSprite::defineSpriteSheet(int frameCount, int cols, int rows, int fps)
{
	object->defineSpriteSheet(frameCount, cols, rows, fps);
}

void LuaSprite::setFrame(int frame)
{
	if (object->isAnimatedSprite() && frame >= 0 && frame < object->getFrameCount())
	{
		object->setFrame(frame);
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

bool LuaSprite::getVisible()
{
	return object->visible();
}

SpriteObject* LuaSprite::getObject()
{
	return object;
}

