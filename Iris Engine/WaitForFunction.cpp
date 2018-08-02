#include "WaitForFunction.h"

WaitForFunction::WaitForFunction(std::function<bool(void)> function)
	:function(function)
{
}

bool WaitForFunction::ready()
{
	return function();
}
