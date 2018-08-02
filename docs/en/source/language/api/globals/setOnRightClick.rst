The setOnRightClick function
============================

:Syntax: setOnRightClick(*function* event)
:Returns: *nil*

Specifies a function to call whenever the player presses the right mouse button.

This can be useful when making custom menus. For example, you could use this function
to close the menu when the player presses the right mouse button.


Parameters
^^^^^^^^^^

+------------+-------+------------------------------------------------+
| Type       | Name  | Description                                    |
+============+=======+================================================+
| *function* | event | The function to call; see remarks_ for details |
+------------+-------+------------------------------------------------+


Remarks
^^^^^^^

Passing *nil* as the argument will disable this event, so pressing the right mouse
button after that will do nothing. Call this function again to re-enable it.


Examples
^^^^^^^^

.. code-block:: lua

    -- You can use this function to close a custom menu
    -- when the player presses the right mouse button
    setOnRightClick(function()
        -- Hide the custom menu
        button1:hide()
        button2:hide()
        button3:hide()

        -- Disable onRightClick event
        setOnRightClick(nil)
    end)