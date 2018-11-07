The setOnMouseEnter method
==========================

:Syntax:
    | setOnMouseEnter(*number* r, *number* g, *number* b, *function* function)
    | setOnMouseEnter(*number* r, *function* function)
:Returns: *nil*

Sets a function to execute when the mouse enters a region with the specified color.


Parameters
^^^^^^^^^^

+------------+----------+--------------------------------------------------------------------+
| Type       | Name     | Description                                                        |
+============+==========+====================================================================+
| *number*   | r        | Red component of the color of the region; see remarks_ for details |
+------------+----------+--------------------------------------------------------------------+
| *number*   | g        | Green component of the color of the region                         |
+------------+----------+--------------------------------------------------------------------+
| *number*   | b        | Blue component of the color of the region                          |
+------------+----------+--------------------------------------------------------------------+
| *function* | function | The function to execute; see remarks_ for details                  |
+------------+----------+--------------------------------------------------------------------+


Remarks
^^^^^^^

If the *function* parameter is *nil*, this event will be disabled.

The second overload of this function only requires the red component of the color.
This will save you some typing for regions where the green and blue channels are set
to 0.


Examples
^^^^^^^^

.. code-block:: lua

    -- Create a clickable map
    map = ClickableMap.new("drawers_map.png")

    -- Play a sound when the mouse enters a region
    -- with the color rgb(255, 0, 0)
    map:setOnMouseEnter(255, function()
        playSound("hover.ogg")
    end)

    -- Enable the map
    map:enable()


See also
^^^^^^^^

* :doc:`setOnMouseExit`
* :doc:`setOnClick`
* :doc:`enable`