The move method
===============

:Syntax: 
	| move(
	|	*number* x,
	|	*number* y,
	|	*number* time,
	|	*bool* shouldBlock,
	|	*Interpolator* interpolator = Interpolator.easeInOut
	| )
:Returns: *nil*

Use this method to start a movement animation where the sprite will move from its
current position to the specified position over time.


Parameters
^^^^^^^^^^

+----------------+--------------+---------------------------------------------------------------+
| Type           | Name         | Description                                                   |
+================+==============+===============================================================+
| *number*       | x            | The x location of the position you want the sprite to move to |
+----------------+--------------+---------------------------------------------------------------+
| *number*       | y            | The y location of the position you want the sprite to move to |
+----------------+--------------+---------------------------------------------------------------+
| *number*       | time         | The duration in seconds of the movement animation             |
+----------------+--------------+---------------------------------------------------------------+
| *bool*         | shouldBlock  | Whether or not this animation should be a blocking transition |
+----------------+--------------+---------------------------------------------------------------+
| *Interpolator* | interpolator | :doc:`Interpolator function<../../enums/interpolator>` to use |
+----------------+--------------+---------------------------------------------------------------+


Remarks
^^^^^^^

.. warning::
    While this method allows you to use non-integer coordinates, keep in mind that if
    a sprite is not aligned with the pixel grid it will look blurry due to anti-aliasing.


Examples
^^^^^^^^

.. code-block:: lua

    -- Create and show a Sprite
    ball = Sprite.new("ball.png", 1)
    ball:show()

    -- Move the ball sprite from its current position to (1112, 81) using an ease-out interpolator
    -- This animation will have a duration of 2 seconds and will be a blocking transition
    ball:move(1112, 81, 2, true, Interpolator.easeOut)

    -- Move the ball back to its starting position using the default interpolator
    ball:move(1112, 81, 2, true)


See also
^^^^^^^^

* :doc:`../../enums/interpolator`
* :doc:`setPosition`
* :doc:`setOrigin`