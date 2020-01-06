The getCurrentTextSize method
=============================

:Syntax: getCurrentTextSize()
:Returns: *number* width, *number* height

Returns the size in pixels of the text currently being displayed.
This is not the maximum size you can specify with :doc:`the setMaxSize method<setMaxSize>`,
but the actual size of the text.


Return values
^^^^^^^^^^^^^

+----------+--------+-----------------------------------------+
| Type     | Name   | Description                             |
+==========+========+=========================================+
| *number* | width  | The width in pixels of the longest line |
+----------+--------+-----------------------------------------+
| *number* | height | The height in pixels of the text        |
+----------+--------+-----------------------------------------+


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

    -- Create a Text object
    local text = Text.new(font, 1)

    -- Set the text to display
    text:setText("This is the text to display")

    -- Set the maximum size of the text
    text:setMaxSize(160, 0)

    -- Get the size
    width, height = text:getCurrentTextSize()

    -- The values returned are
    -- width = 134
    -- height = 99


See also
^^^^^^^^

* :doc:`constructor`
* :doc:`setMaxSize`