The disable method
==================

:Syntax: disable()
:Returns: *nil*

This method is used to disable a ClickableMap object.

After a call to this method, the player will not be able to interact with the
clickable map.


Examples
^^^^^^^^

.. code-block:: lua

    -- Create a clickable map
    map = ClickableMap.new("drawers_map.png")

    -- Disable the map when the mouse enters a region
    -- with the color rgb(255, 0, 0)
    map:setOnMouseEnter(255, function()
        map:disable()
    end)

    -- Enable the map
    map:enable()

    -- map:enable() is a blocking function, so this text will only
    -- show up after the map has been disbled
    say "The clickable map has been disabled."


See also
^^^^^^^^

* :doc:`enable`
* :doc:`disableOnClick`
* :doc:`setOnMouseEnter`