#include "LuaObject.h"
#include "Object.h"
#include "GameObjectManager.h"
#include "Object.h"
#include "WaitQueue.h"
#include "WaitForTransition.h"
#include "Locator.h"
#include "TransitionUtils.h"
#include "LuaEnvironment.h"

LuaObject::LuaObject(GameObjectManager* gom, LuaEnvironment* lua, Object* object)
	:gameObjectManager(gom),
	 lua(lua),
	 object(object)
{
	// Add sprite to game object manager
	gameObjectManager->add(object);
}

LuaObject::~LuaObject()
{
	// Remove object from game object manager and delete it
	bool success = gameObjectManager->remove(object);

	if (success)
		delete object;
	
	// Can't log because logger may not exist at this point
}

void LuaObject::show()
{
	// By default, sprites show with a non-blocking 0.3 seconds fade
	object->startFadeIn(0.3f, false);
}

void LuaObject::showTransition(const sol::table& transition, sol::this_state s)
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

void LuaObject::hide()
{
	// By default, sprites hide with a non-blocking 0.3 seconds fade
	object->startFadeOut(0.3f, false);
}

void LuaObject::hideTransition(const sol::table & transition, sol::this_state s)
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

void LuaObject::setAlpha(uint8_t alpha)
{
	object->setAlpha(alpha);
}

void LuaObject::skipTransition()
{
	object->skipTransition();
}

void LuaObject::setPosition(float x, float y)
{
	object->skipMovement();
	object->setPosition(x, y);
}

std::tuple<float, float> LuaObject::getPosition()
{
	Vector2<float> position = object->getPosition();
	return std::make_tuple(position.x, position.y);
}

void LuaObject::setOrigin(int x, int y)
{
	object->setOrigin(x, y);
}

void LuaObject::move(float x, float y, float time, bool shouldBlock, sol::this_state s)
{
	moveInterpolator(x, y, time, shouldBlock, InterpolatorType::DEFAULT, s);
}

void LuaObject::moveInterpolator(
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

bool LuaObject::getVisible()
{
	return object->visible();
}

Object* LuaObject::getObject()
{
	return object;
}

LuaEnvironment* LuaObject::getLua()
{
	return lua;
}

