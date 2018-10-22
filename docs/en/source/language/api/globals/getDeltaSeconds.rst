The getDeltaSeconds function
============================

:Syntax: getDeltaSeconds()
:Returns: *number* elapsedSeconds

Returns the number of seconds elapsed since the last execution of Lua code.

This can be used in combination with :doc:`the yield function<yield>` to extend
the game loop with your own custom code, allowing you to create minigames where the
speed of the game does not depend on the frame rate.

You can also use this function to know how much time the player spent reading a
certain line or making a certain decision.


Return values
^^^^^^^^^^^^^

+----------+----------------+---------------------------------------------------------------------------------+
| Type     | Name           | Description                                                                     |
+==========+================+=================================================================================+
| *number* | elapsedSeconds | The time elapsed since the last execution of lua code; see remarks_ for details |
+----------+----------------+---------------------------------------------------------------------------------+


Remarks
^^^^^^^

The value returned is the number of seconds elapsed from the beginning of the last Lua
execution to the beginning of the current Lua execution.

Examples
^^^^^^^^

.. code-block:: lua

	-- Create a question
	q = Question.new{
	    "Have a drink", 0,
	    "Have an ice cream", 1
	}

	-- Ask the player what to do
	say "What should I do?"
	q:ask()

	-- Get the time elapsed since q:ask() was called
	-- This works because q:ask is a blocking function (see glossary for details)
	elapsedTime = getDeltaSeconds()
	say ("You have spent " .. elapsedTime .. " seconds making that decision.")


See also
^^^^^^^^

* :doc:`yield`
* :term:`Blocking function`