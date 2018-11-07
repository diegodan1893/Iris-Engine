The setOnClick method
==========================

:Syntax:
    | setOnClick(*number* r, *number* g, *number* b, *function* function)
    | setOnClick(*number* r, *function* function)
:Returns: *nil*

Sets a function to execute when the player clicks on a region with the specified
color.


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

If :doc:`the disableOnClick property<disableOnClick>` is set to ``true``, the map
will be disabled automatically before the provided function is executed. This is only
true for regions where this event is enabled (the *function* is not *nil*).

The second overload of this function only requires the red component of the color.
This will save you some typing for regions where the green and blue channels are set
to 0.


Examples
^^^^^^^^

.. code-block:: lua

    -- Show a background with three drawers to the player
    scene("drawers.png")

    -- Create a clickable map
    map = ClickableMap.new("drawers_map.png")

    -- Define the function to call when the player clicks a region with
    -- the color rgb(255, 0, 0)
    map:setOnClick(255, 0, 0, function()
        say "This is the first drawer."
        hideText()
    end)

    -- Define the function to call when the player clicks a region with
    -- the color rgb(0, 255, 0)
    map:setOnClick(0, 255, 0, function()
        say "This is the second drawer."
        hideText()
    end)

    -- Define the function to call when the player clicks a region with
    -- the color rgb(0, 0, 255)
    map:setOnClick(0, 0, 255, function()
        say "This is the third drawer."
        hideText()
    end)

    -- Enable the clickable map
    map:enable()


See also
^^^^^^^^

* :doc:`setOnMouseEnter`
* :doc:`setOnMouseClick`
* :doc:`enable`
* :doc:`disableOnClick`