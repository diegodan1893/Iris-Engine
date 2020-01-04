The ellipsis property
=====================

If the Text object has a maximum size, the text might be too long to fit. In such cases,
the string set in this property will be apended to the displayed text so that the player is
aware of this fact.


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
    text:setMaxSize(160, 1)
    text:show()

    -- Set the ellipsis string (the default value is "...")
    text.ellipsis = "--"

    -- The player will see the following text:
    -- "This is the te--"


See also
^^^^^^^^

* :doc:`setMaxSize`