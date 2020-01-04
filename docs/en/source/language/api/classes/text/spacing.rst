The spacing property
====================

Sets the line spacing in pixels. This will be added to the recommended line spacing of your
font, which it's usually a few more pixels than necessary for lines to not overlap. Negative
numbers bring lines together.


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

    -- Set a max size and the text to display
    text:setText("This is the text to display")
    text:setMaxSize(160, 0)
    text:show()

    -- Set the line spacing so that lines are a bit closer
    text.spacing = -5


See also
^^^^^^^^

* :doc:`setMaxSize`