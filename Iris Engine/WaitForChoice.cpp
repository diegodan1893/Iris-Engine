#include "WaitForChoice.h"
#include "ButtonMenu.h"
#include "LuaQuestion.h"

WaitForChoice::WaitForChoice(ButtonMenu* menu, LuaQuestion* question)
	:menu(menu),
	 question(question)
{
}

bool WaitForChoice::ready()
{
	bool isReady = menu->ready() && !menu->inTransition();

	if (isReady)
		question->setAnswer(menu->getSelectedButton());

	return isReady;
}
