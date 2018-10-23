The Question class
==================

Many visual novels ask the player to make choices that influence the outcome of the
story. In Iris Engine, this can be done using Question objects. Let's see an example:

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

In order to create a Question object, you will need to specify the list of options
the player can choose. This is done using a *table* that contains exactly two entries
for each option: a *string* with the text of the button, and a value to associate to
that option. In the previous example that value was a *function* with the code to
execute if the player selects that option, but this value can be anything, including
numbers, booleans, objects, strings and so on.

The choice is presented to the player using :doc:`the ask method<ask>`. After the call
to this method has returned, :doc:`the answer property<answer>` of the object will
contain the value associated with the option that the player selected. If this value
was a function, that function will be called automatically.


Properties
^^^^^^^^^^

.. toctree::
    :hidden:

    answer
    removeAfterSelection
    count

.. table::
    :widths: 1 1 1 100

    +---------+---------------------------------------------------+---------------+-------------------------------------------------------------------------------------+
    | Type    | Name                                              | Default value | Description                                                                         |
    +=========+===================================================+===============+=====================================================================================+
    | *any*   | :doc:`answer<answer>`                             | *undefined*   | Gets the value associated with the option selected by the player                    |
    +---------+---------------------------------------------------+---------------+-------------------------------------------------------------------------------------+
    | *bool*  | :doc:`removeAfterSelection<removeAfterSelection>` | *false*       | Gets or sets whether or not options should be removed after the player selects them |
    +---------+---------------------------------------------------+---------------+-------------------------------------------------------------------------------------+
    | *count* | :doc:`count<count>`                               |               | Gets the number of options in a Question                                            |
    +---------+---------------------------------------------------+---------------+-------------------------------------------------------------------------------------+


Member functions
^^^^^^^^^^^^^^^^

.. toctree::
    :hidden:

    constructor
    ask

.. table::
    :widths: 1 100

    +-----------------------------------+----------------------------------+
    | Method                            | Description                      |
    +===================================+==================================+
    | :doc:`(constructor)<constructor>` | Create a Question object         |
    +-----------------------------------+----------------------------------+
    | :doc:`ask<ask>`                   | Present the choice to the player |
    +-----------------------------------+----------------------------------+
