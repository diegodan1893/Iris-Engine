The __call metamethod
=====================

:Syntax: character(*string* text)
:Returns: *nil*

The __call metamethod allows you to treat a Character object like a function.
This allows you to use a Character object in the same way as
:doc:`the say function<../../globals/say>` to write **dialogue**, which consists of
text labeled with the name of the character that is saying it.

The given text will be displayed in the :term:`text window` with a typewriter effect.
After that, the execution of the script will be paused until the player clicks to
dismiss it.

If the text contains a ``\n`` character, a line break will be inserted.

If the text to display is too long to fit in the :term:`text window`, it will be
splitted automatically as if you had written it using multiple calls to the
metamethod.


Parameters
^^^^^^^^^^

+----------+------+---------------------------------+
| Type     | Name | Description                     |
+==========+======+=================================+
| *string* | text | The text to display as dialogue |
+----------+------+---------------------------------+


.. Return value


Remarks
^^^^^^^

If the argument is a single literal string, the parentheses can be omitted, making a
call to the method look like this: ``character "Text."``. This will save you
a lot of typing.

If the :term:`text window` is hidden, it will be made visible with the transition
specified in the :doc:`config file<../../../../config>`.


Examples
^^^^^^^^

.. code-block:: lua

    -- Create Character objects for Haru and Sakura
    h = Character.new("Haru")
    s = Character.new("Sakura")

    -- Display dialogue using the variables we defined above
    h "Hi, my name is Haru."
    s "And I am Sakura."

    -- Using this metamethod with variables and expressions
    a = 10
    b = "Hello!"
    h("The value of a is " .. a .. ".")
    s(b)


See also
^^^^^^^^

* :doc:`../../globals/say`
* :doc:`../../globals/append`