The removeAfterSelection property
=================================

Gets or sets whether or not options should be removed from the Question object in
subsequent calls to :doc:`the ask method<ask>` after the player selects them.

This can be used, for example, in games where the player is required to ask a set of
questions to a character and is able to decide in which order to ask them.


Examples
^^^^^^^^

.. code-block:: lua

	-- Create a Question object
	q = Question.new{
	    "Let's talk about the weather", 0,
	    "Are you a cat or a dog person?", 1,
	    "Let's talk about the sociopolitical situation", 2
	}

	-- Remove options after the player selects them
	q.removeAfterSelection = true

	-- Let the player select an option until there are no more options to select
	while q.count > 0 do
	    -- Text of the question
	    s "What do you want to talk about?"

	    -- Show the choices to the player
	    q:ask()
	end


See also
^^^^^^^^

* :doc:`ask`
* :doc:`count`