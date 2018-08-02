The name property
=================

Gets or sets the text that will be displayed as the name of the character in the
:term:`text window` when this character speaks.


Examples
^^^^^^^^

.. code-block:: lua

    -- Characters
    h = Character.new("Haru")
    s = Character.new("???")

    -- Dialogue
    s "Good morning!"   --> The name will be displayed as "???"
    h "Hi. What's your name?"

    -- Set the name to "Sakura"
    s.name = "Sakura"

    s ("My name is " .. s.name .. ". Nice to meet you.")
    --> The text displayed will be: "My name is Sakura. Nice to meet you."


See also
^^^^^^^^

* :doc:`constructor`
* :doc:`call`