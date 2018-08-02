#include "WaitForTransition.h"
#include "Object.h"

WaitForTransition::WaitForTransition(Object* object)
	:object(object)
{
}

bool WaitForTransition::ready()
{
	return !object->inTransition();
}
