The setText method
==================

:Syntax: setText(*string* text)
:Returns: *nil*

Sets the string to display by this Text object.


Parameters
^^^^^^^^^^

+----------+------+---------------------+
| Type     | Name | Description         |
+==========+======+=====================+
| *string* | text | The text to display |
+----------+------+---------------------+


Examples
^^^^^^^^

.. code-block:: lua

    -- Font properties
    font = {
        file = "assets/fonts/Roboto-Medium.ttf",
        size = 28,
        color = {r = 255, g = 255, b = 255, a = 255},
        shadowDistance = 0,
        shadowColor = {r = 0, g = 0, b = 0, a = 0}
    }

    -- Create text object
    text = Text.new(font, 1)

    -- Set the text and show the object
    text:setText("This is an example")
    text:show()


See also
^^^^^^^^

* :doc:`constructor`