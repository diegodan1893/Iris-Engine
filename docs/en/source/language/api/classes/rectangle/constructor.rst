Rectangle constructor
=====================

:Syntax: Rectangle.new(*number* zindex)

Constructs a Rectangle object.

This object will be placed at coordinates (0, 0), and its origin will be the top
left corner.


Parameters
^^^^^^^^^^

+----------+--------+----------------------------+
| Type     | Name   | Description                |
+==========+========+============================+
| *number* | zindex | The z-index of this sprite |
+----------+--------+----------------------------+


Examples
^^^^^^^^

.. code-block:: lua

    -- Create a rectagle
    rect = Rectangle.new(3)

    -- Set color and size
    rect:setColor({r = 255, g = 0, b = 0, a = 255})
    rect:setSize(15, 55)

    -- Show it
    rect:show()


See also
^^^^^^^^

* :doc:`setColor`
* :doc:`setSize`
* :doc:`../sprite/top`