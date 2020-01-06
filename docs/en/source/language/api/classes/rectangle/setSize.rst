The setSize method
==================

:Syntax: setSize(*number* width, *number* height)
:Returns: *nil*

Sets the size of the rectangle.


Parameters
^^^^^^^^^^

+----------+--------+----------------------+
| Type     | Name   | Description          |
+==========+========+======================+
| *number* | width  | The width in pixels  |
+----------+--------+----------------------+
| *number* | height | The height in pixels |
+----------+--------+----------------------+


Examples
^^^^^^^^

.. code-block:: lua

    -- Create a rectagle
    rect = Rectangle.new(3)

    -- Set color, size and position
    rect:setColor({r = 255, g = 0, b = 0, a = 255})
    rect:setSize(15, 55)
    rect:setPosition(50, 50)

    -- Show it
    rect:show()


See also
^^^^^^^^

* :doc:`setColor`
* :doc:`constructor`