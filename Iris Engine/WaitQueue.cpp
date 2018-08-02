#include "WaitQueue.h"
#include "WaitCommand.h"

WaitQueue::WaitQueue()
{
}

WaitQueue::~WaitQueue()
{
	while (!queue.empty())
		pop();
}

bool WaitQueue::empty() const
{
	return queue.empty();
}

void WaitQueue::push(WaitCommand* command)
{
	queue.push(command);
}

WaitCommand* WaitQueue::front()
{
	return queue.front();
}

void WaitQueue::pop()
{
	WaitCommand* command = queue.front();
	delete command;
	queue.pop();
}
