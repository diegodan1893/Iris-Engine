#include "WaitForVisible.h"
#include "Object.h"

WaitForVisible::WaitForVisible(Object* object, bool visible)
	:object(object),
	 visible(visible)
{
}

bool WaitForVisible::ready()
{
	return object->visible() == visible;
}
