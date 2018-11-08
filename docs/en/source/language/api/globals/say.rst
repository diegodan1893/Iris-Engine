The say function
================

:Syntax: say(*string* text)
:Returns: *nil*

This function is used to write **narration**, which consists of text that doesn't have
a speaker.

The given text will be displayed in the :term:`text window` with a typewriter effect.
After that, the execution of the script will be paused until the player clicks to
dismiss it.

If the text contains a ``\n`` character, a line break will be inserted.

If the text to display is too long to fit in the :term:`text window`, it will be
splitted automatically as if you had written it using multiple calls to the say
function.


Parameters
^^^^^^^^^^

+----------+------+----------------------------------+
| Type     | Name | Description                      |
+==========+======+==================================+
| *string* | text | The text to display as narration |
+----------+------+----------------------------------+


.. Return value


Remarks
^^^^^^^

If the argument is a single literal string, the parentheses can be omitted, making a
call to the function look like this: ``say "Text."``. This will save you a lot of
typing.

If the :term:`text window` is hidden, it will be made visible with the transition
specified in the :doc:`config file<../../../config>`.


Examples
^^^^^^^^

.. code-block:: lua

    -- Using the 'say' function with literal strings
    say "This is narration."
    say "As this is a single literal string, the parentheses can be omitted."
    say "Easy, right?"

    -- Using the 'say' function with variables and expressions
    a = 10
    b = "Hello!"
    say("The value of a is " .. a .. ".")
    say(b)


See also
^^^^^^^^

* :doc:`append`
* :doc:`../classes/character/top`