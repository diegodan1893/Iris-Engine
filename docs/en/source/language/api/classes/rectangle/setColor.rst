The setColor method
===================

:Syntax: setColor(*table* color)
:Returns: *nil*

Sets the color of the rectangle.


Parameters
^^^^^^^^^^

+---------+-------+-------------------------------------+
| Type    | Name  | Description                         |
+=========+=======+=====================================+
| *table* | color | The color; see remarks_ for details |
+---------+-------+-------------------------------------+


Remarks
^^^^^^^

The *color* argument should be a table with the following fields:

+----------+------+---------------------------------------+
| Type     | Name | Description                           |
+==========+======+=======================================+
| *number* | r    | The red value in the range [0, 255]   |
+----------+------+---------------------------------------+
| *number* | g    | The green value in the range [0, 255] |
+----------+------+---------------------------------------+
| *number* | b    | The blue value in the range [0, 255]  |
+----------+------+---------------------------------------+
| *number* | a    | The alpha value in the range [0, 255] |
+----------+------+---------------------------------------+


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

* :doc:`setSize`
* :doc:`constructor`