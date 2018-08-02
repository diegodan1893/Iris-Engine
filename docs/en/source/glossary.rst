Glossary
========

.. glossary::

	Text window
		The box where dialogue and narration will appear.

	Blocking transition
		A transition that pauses the execution of the script until it has finished.
		This means that if you declare two blocking transitions one after another in a
		script, the second one will not start until the first one has been completed.

	Non-blocking transition
		A transition that doesn't pause the execution of the script. This means that
		if you declare two non-blocking transitions one after another in a script,
		both of them will start at the same time.

	Blocking function
		A function that suspends the execution of the script until a certain condition
		has been met. Examples of such functions are the
		:doc:`say<language/api/globals/say>` and the
		:doc:`sleep<language/api/globals/sleep>` functions.