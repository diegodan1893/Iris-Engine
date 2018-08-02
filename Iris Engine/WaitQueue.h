#pragma once

#include <queue>

class WaitCommand;

/// <summary>
/// A queue of pending <see cref="WaitCommand"/>s
/// to extecute.
/// </summary>
class WaitQueue
{
public:
	WaitQueue();
	~WaitQueue();
	
	/// <summary>
	/// Check if the queue is empty.
	/// </summary>
	/// <returns><c>true</c> if the queue is empty; otherwise, <c>false</c>.</returns>
	bool empty() const;
	
	/// <summary>
	/// Pushes the specified command.
	/// </summary>
	/// <param name="command">The command.</param>
	void push(WaitCommand* command);
	
	/// <summary>
	/// Returns the command at the front of the queue.
	/// </summary>
	/// <returns>The command at the front of the queue.</returns>
	WaitCommand* front();
	
	/// <summary>
	/// Pops the command at the front of the queue.
	/// </summary>
	void pop();

private:
	std::queue<WaitCommand*> queue;
};
