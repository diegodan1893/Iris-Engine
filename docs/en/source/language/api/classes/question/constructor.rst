Question constructor
====================

:Syntax: Question.new(*table* choices)

Constructs a Question object with the specified choices.


Parameters
^^^^^^^^^^

+---------+---------+------------------------------------------------------------------------+
| Type    | Name    | Description                                                            |
+=========+=========+========================================================================+
| *table* | choices | A list of options the player can choose from; see remarks_ for details |
+---------+---------+------------------------------------------------------------------------+


Remarks
^^^^^^^

The list of options must be a *table* that contains exactly two entries for each
option in the following order:

+----------+-------+-------------------------------------------------------------+
| Type     | Name  | Description                                                 |
+==========+=======+=============================================================+
| *string* | text  | The text that will be displayed in the menu for this option |
+----------+-------+-------------------------------------------------------------+
| *any*    | value | A value of any type associated to this option               |
+----------+-------+-------------------------------------------------------------+

The choice is presented to the player using :doc:`the ask method<ask>`. After the
call to this method has returned, :doc:`the answer property<answer>` of the object
will contain the value associated with the option that the player selected. If this
value was a function, that function will be called automatically.

When the argument of a function is a single table the parentheses can be omitted,
so instead of ``Question.new({ ... })``, you can use ``Question.new{ ... }``.


Examples
^^^^^^^^

Question object where the value associated to each option is a function:

.. code-block:: lua

	-- First, we define a function for each option
	function drink()
	    say "I'm thirsty too. I should have a drink."
	end

	function iceCream()
	    say "Ice cream is probably the best option."
	end

	-- Then we create a Question object by giving it a list of options and
	-- the corresponding functions to call when the player selects them
	q = Question.new{
	    "Have a drink", drink,
	    "Have an ice cream", iceCream
	}

	-- We can ask the player by calling q:ask()
	say "It's so hot here. What should I do?"
	q:ask()
	-- The function corresponding to the selected option will be called automatically

An alternative way to create the same Question object:

.. code-block:: lua

	-- This time, we will define the functions while creating the question
	q = Question.new{
	    "Have a drink", function()
	        say "I'm thirsty too. I should have a drink."
	    end,

	    "Have an ice cream", function()
	        say "Ice cream is probably the best option."
	    end
	}

	-- Now we can ask the player to make the choice
	say "It's so hot here. What should I do?"
	q:ask()

Question object where the value associated to each option is not a function:

.. code-block:: lua

	-- Language selector
	local q = Question.new{
	    "日本語", "ja/",
	    "English", "en/",
	    "Español", "es/"
	}

	-- Ask the player to select a language
	q:ask()

	-- Save the selected language in a global variable
	-- so that all scripts can check it
	lang = q.answer
	--> Will be "ja/", "en/" or "es/" depending on the option selected by the player