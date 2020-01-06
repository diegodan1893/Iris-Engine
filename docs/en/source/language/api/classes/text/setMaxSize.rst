The setMaxSize method
=====================

:Syntax: setMaxSize(*number* width, *number* height)
:Returns: *nil*

Sets a maximum size in pixels for the text.

The text will be split in lines or truncated so that it fits the specified size.


Parameters
^^^^^^^^^^

+----------+--------+--------------------------------------------------------+
| Type     | Name   | Description                                            |
+==========+========+========================================================+
| *number* | width  | The maximum width in pixels; see remarks_ for details  |
+----------+--------+--------------------------------------------------------+
| *number* | height | The maximum height in pixels; see remarks_ for details |
+----------+--------+--------------------------------------------------------+


Remarks
^^^^^^^

Specifying a value of 0 for either width or height will disable this feature for that
axis, allowing the text to grow infinitely.

Regardless of the maximum height specified, the Text class will always display at least one
line of text, so setting this value to ``1`` is an easy way to limit the height of the text
to one line.


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

    -- Set the maximum size to 160 pixels horizontally
    -- and one line of text vertically
    text:setMaxSize(160, 1)

    -- Set the maximum size to 160 pixels horizontally
    -- and 500 pixels vertically
    text:setMaxSize(160, 500)


See also
^^^^^^^^

* :doc:`constructor`
* :doc:`ellipsis`
* :doc:`spacing`