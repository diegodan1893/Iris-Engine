The getMousePosition function
==============================

:Syntax: getMousePosition()
:Returns: *number* x, *number* y

Returns the position of the mouse.


Return values
^^^^^^^^^^^^^

+----------+------+--------------------------------------------------------------------------+
| Type     | Name | Description                                                              |
+==========+======+==========================================================================+
| *number* | x    | Distance in pixels from the left side of the screen to the mouse pointer |
+----------+------+--------------------------------------------------------------------------+
| *number* | y    | Distance in pixels from the top of the screen to the mouse pointer       |
+----------+------+--------------------------------------------------------------------------+


Examples
^^^^^^^^

.. code-block:: lua

    -- Get the position of the mouse
    x, y = getMousePosition()


See also
^^^^^^^^

* :doc:`enableMouseInput`
* :doc:`disableMouseInput`