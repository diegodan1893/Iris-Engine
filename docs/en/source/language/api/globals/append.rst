The append function
===================

:Syntax: append(*string* text)
:Returns: *nil*

Adds new text to the :term:`text window` without clearing what was already being
displayed. After that, the execution of the script will be paused until the player
clicks to dismiss it.

This function works with both **dialogue** and **narration**.


Parameters
^^^^^^^^^^

+----------+------+--------------------+
| Type     | Name | Description        |
+==========+======+====================+
| *string* | text | The text to append |
+----------+------+--------------------+


.. Return value


Remarks
^^^^^^^

If the argument is a single literal string, the parentheses can be omitted, making a
call to the function look like this: ``append "Text."``. This will save you a lot of
typing.


Examples
^^^^^^^^

.. code-block:: lua

    -- Using the 'append' function with narration
    say "This is bad."
    say "I shouldn't be here"
    append ", should I?"


See also
^^^^^^^^

* :doc:`say`
* :doc:`../character`