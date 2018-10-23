The count property
=================================

Gets the number of options the player will be able to select when
:doc:`the ask method<ask>` is called.


Examples
^^^^^^^^

.. code-block:: lua

	-- Create a Question object
	q = Question.new{
	    "Let's talk about the weather", 0,
	    "Are you a cat or a dog person?", 1,
	    "Let's talk about the sociopolitical situation", 2
	}
	--> At this moment, q.count is 3

	-- Remove options after the player selects them
	-- This will decrease the value of q.count each time the player selects an option
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
* :doc:`removeAfterSelection`