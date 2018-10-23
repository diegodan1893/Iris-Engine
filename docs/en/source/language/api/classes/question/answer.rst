The answer property
===================

After a call to :doc:`the ask method<ask>`, gets the value associated to the option
selected by the player.

.. warning::
	The value of this property before a call to :doc:`the ask method<ask>` is
	undefined.


Examples
^^^^^^^^

.. code-block:: lua

	say "I have to choose heads or tails."

	-- We will associate a number to each option
	q = Question.new{
	    "Heads", 0, -- A value of 0 will mean heads
	    "Tails", 1  -- A value of 1 will mean tails
	}

	-- Ask the player to choose
	q:ask()

	-- Check the answer
	result = q.asnwer  -- Will be '0' if the player selected "Heads"
	                   -- or '1' if the player selected "Tails"


See also
^^^^^^^^

* :doc:`ask`
* :doc:`constructor`