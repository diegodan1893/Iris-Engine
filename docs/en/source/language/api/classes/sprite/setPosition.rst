The setPosition method
======================

:Syntax: setPosition(*number* x, *number* y)
:Returns: *nil*

This method is used to set the position of the sprite.


Parameters
^^^^^^^^^^

+----------+------+-----------------------------------------------------+
| Type     | Name | Description                                         |
+==========+======+=====================================================+
| *number* | x    | Distance in pixels from the left side of the screen |
+----------+------+-----------------------------------------------------+
| *number* | y    | Distance in pixels from the top of the screen       |
+----------+------+-----------------------------------------------------+


Remarks
^^^^^^^

The exact pixel of the image that lands in the provided position is called the
**origin**. You can change the origin of a sprite with
:doc:`the setOrigin method<setOrigin>`.


Examples
^^^^^^^^

.. code-block:: lua

    -- Create a sprite
    ball = Sprite.new("ball.png", 1)

    -- Place it in the position (50, 60)
    ball:setPosition(50, 60)


See also
^^^^^^^^

* :doc:`setOrigin`
* :doc:`getPosition`