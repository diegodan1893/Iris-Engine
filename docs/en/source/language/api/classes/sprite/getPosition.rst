The getPosition method
======================

:Syntax: getPosition()
:Returns: *number* x, *number* y

This method returns the current position of the sprite.


Return values
^^^^^^^^^^^^^

+----------+------+-----------------------------------------------------+
| Type     | Name | Description                                         |
+==========+======+=====================================================+
| *number* | x    | Distance in pixels from the left side of the screen |
+----------+------+-----------------------------------------------------+
| *number* | y    | Distance in pixels from the top of the screen       |
+----------+------+-----------------------------------------------------+


Examples
^^^^^^^^

.. code-block:: lua

	-- Create a sprite and place it in the position (50, 60)
	ball = Sprite.new("ball.png", 1)
	ball:setPosition(50, 60)

	-- Get its position with the getPosition method
	x, y = ball:getPosition()
	--> Now, x = 50 and y = 60


See also
^^^^^^^^

* :doc:`setOrigin`
* :doc:`setPosition`