The ask method
==============

:Syntax: ask()
:Returns: *nil*

This method is used to show the player a menu with the options of this question.

The execution of the script will be paused until the player has slected one of the
options, after which :doc:`the answer property<answer>` will contain the value
associated with the option the player selected. If this value was a function, that
function will be called automatically.

The appearance of the menu can be customized in the
:doc:`config file<../../../../config>`.


Examples
^^^^^^^^

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

See also
^^^^^^^^

* :doc:`answer`