#include "TransitionUtils.h"
#include "LinearInterpolator.h"
#include "EaseInInterpolator.h"
#include "EaseOutInterpolator.h"
#include "EaseInOutInterpolator.h"
#include "Locator.h"

bool TransitionUtils::getTransitionType(const sol::table& transition, TransitionType& outTransitionType)
{
	sol::object luaTransitionType = transition["type"];

	if (luaTransitionType.is<TransitionType>())
	{
		outTransitionType = luaTransitionType.as<TransitionType>();
		return true;
	}
	else
	{
		error(u8"A transition type needs to be specified");
		return false;
	}
}

bool TransitionUtils::getTransitionTime(const sol::table& transition, float& outTransitionTime)
{
	sol::object luaTransitionTime = transition["time"];

	if (luaTransitionTime.is<float>())
	{
		outTransitionTime = luaTransitionTime.as<float>();
		return true;
	}
	else
	{
		error(u8"A transition time needs to be specified");
		return false;
	}
}

bool TransitionUtils::getTransitionBlocking(const sol::table& transition, bool& outShouldBlock)
{
	sol::object luaTransitionBlock = transition["block"];

	if (luaTransitionBlock.is<bool>())
	{
		outShouldBlock = luaTransitionBlock.as<bool>();
		return true;
	}
	else
	{
		error(u8"Use block=true or block=false to specify whether the script execution should be blocked until the transition has finished");
		return false;
	}
}

bool TransitionUtils::getTransitionImage(const sol::table& transition, std::string& outImage)
{
	sol::object luaTransitionImage = transition["image"];

	if (luaTransitionImage.is<std::string>())
	{
		outImage = luaTransitionImage.as<std::string>();
		return true;
	}
	else
	{
		error(u8"A transition image needs to be specified");
		return false;
	}
}

Interpolator* TransitionUtils::getInterpolator(InterpolatorType type)
{
	Interpolator* interpolator = nullptr;

	switch (type)
	{
	case InterpolatorType::LINEAR:
		interpolator = new LinearInterpolator();
		break;

	case InterpolatorType::QUADRATIC_IN:
		interpolator = new EaseInInterpolator();
		break;

	case InterpolatorType::QUADRATIC_OUT:
		interpolator = new EaseOutInterpolator();
		break;

	case InterpolatorType::QUADRATIC_IN_OUT:
		interpolator = new EaseInOutInterpolator();
		break;

	case InterpolatorType::DEFAULT:
		interpolator = new EaseInOutInterpolator();
		break;

	default:
		Locator::getLogger()->log(LogCategory::LUA, LogPriority::ERROR, u8"Invalid interpolator type.");
		interpolator = new EaseInOutInterpolator();
		break;
	}

	return interpolator;
}

void TransitionUtils::error(const std::string & message)
{
	Locator::getLogger()->log(LogCategory::LUA, LogPriority::ERROR, message);
}
