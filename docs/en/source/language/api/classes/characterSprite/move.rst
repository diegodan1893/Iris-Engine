The move method
===============

:Syntax: 
    | move(
    |   *number* x,
    |   *number* y,
    |   *number* time,
    |   *bool* shouldBlock,
    |   *Interpolator* interpolator = Interpolator.easeInOut
    | )
    | move(
    |   *Position* position,
    |   *number* time,
    |   *bool* shouldBlock,
    |   *Interpolator* interpolator = Interpolator.easeInOut
    | )
:Returns: *nil*

Use this method to start a movement animation where the character sprite will move
from its current position to the specified position over time.


Parameters
^^^^^^^^^^

+----------------+--------------+-----------------------------------------------------------------------+
| Type           | Name         | Description                                                           |
+================+==============+=======================================================================+
| *number*       | x            | The x location of the position you want the sprite to move to         |
+----------------+--------------+-----------------------------------------------------------------------+
| *number*       | y            | The y location of the position you want the sprite to move to         |
+----------------+--------------+-----------------------------------------------------------------------+
| *Position*     | position     | The position you want the sprite to move to; see remarks_ for details |
+----------------+--------------+-----------------------------------------------------------------------+
| *number*       | time         | The duration in seconds of the movement animation                     |
+----------------+--------------+-----------------------------------------------------------------------+
| *bool*         | shouldBlock  | Whether or not this animation should be a blocking transition         |
+----------------+--------------+-----------------------------------------------------------------------+
| *Interpolator* | interpolator | :doc:`Interpolator function<../../enums/interpolator>` to use         |
+----------------+--------------+-----------------------------------------------------------------------+


Remarks
^^^^^^^

The exact pixel of the image that lands in the provided position is called the
**origin**. The origin of character sprites is located at the bottom center of the
sprite.

If you use the Position enum, the bottom of the character sprite will be aligned with
the bottom of the screen. Additionally:

* ``Position.left`` will align the left side of the character sprite with the left side of the screen
* ``Position.center`` will center the sprite horizontally
* ``Position.right`` will align the right side of the character sprite with the right side of the screen


Examples
^^^^^^^^

.. code-block:: lua

    -- Define a character sprite and make it visible
    sakura = CharacterSprite.new("sakura1.png")
    sakura:show("smiling")

    -- Move the sprite from its current position to (80, 700) using an ease-in-out interpolation
    -- This animation will have a duration of 1 second and will be a blocking transition
    sakura:move(80, 700, 1, true)

    -- Move the sprite to the right side of the screen using an ease-out interpolation
    -- This animation will have a duration of 1 second and will be a non-blocking transition
    sakura:move(Position.right, 1, false, Interpolator.easeOut)


See also
^^^^^^^^

* :doc:`moveX`
* :doc:`../../enums/interpolator`
* :doc:`setPosition`
* :doc:`setX`
