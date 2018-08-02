#pragma once

#include "TransitionType.h"
#include "InterpolatorType.h"
#include <string>
#include <sol.hpp>

/// <summary>
/// Helper class to easily check transition parameters.
/// </summary>
class TransitionUtils
{
public:
	static bool getTransitionType(const sol::table& transition, TransitionType& outTransitionType);
	static bool getTransitionTime(const sol::table& transition, float& outTransitionTime);
	static bool getTransitionBlocking(const sol::table& transition, bool& outShouldBlock);
	static bool getTransitionImage(const sol::table& transition, std::string& outImage);
	static class Interpolator* getInterpolator(InterpolatorType type);

private:
	static void error(const std::string& message);
};