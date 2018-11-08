The moveX method
================

:Syntax: 
	| moveX(
	|	*number* x,
	|	*number* time,
	|	*bool* shouldBlock,
	|	*Interpolator* interpolator = Interpolator.easeInOut
	| )
:Returns: *nil*

Most of the time you will only need to move the character sprite horizontally.
This method allows you to move the character sprite along the ``x`` axis. The final
``y`` position of the movement will be automatically calculated so that the bottom
of the sprite is aligned with the bottom of the screen.


Parameters
^^^^^^^^^^

+----------------+--------------+---------------------------------------------------------------+
| Type           | Name         | Description                                                   |
+================+==============+===============================================================+
| *number*       | x            | The x location of the position you want the sprite to move to |
+----------------+--------------+---------------------------------------------------------------+
| *number*       | time         | The duration in seconds of the movement animation             |
+----------------+--------------+---------------------------------------------------------------+
| *bool*         | shouldBlock  | Whether or not this animation should be a blocking transition |
+----------------+--------------+---------------------------------------------------------------+
| *Interpolator* | interpolator | :doc:`Interpolator function<../../enums/interpolator>` to use |
+----------------+--------------+---------------------------------------------------------------+


Remarks
^^^^^^^

The exact pixel of the image that lands in the provided position is called the
**origin**. The origin of character sprites is located at the bottom center of the
sprite.


Examples
^^^^^^^^

.. code-block:: lua

    -- Define a character sprite and make it visible
    sakura = CharacterSprite.new("sakura1.png")
    sakura:show("smiling")

    -- Move the sprite from its current position to x=80 using an ease-in-out interpolation
    -- This animation will have a duration of 1 second and will be a blocking transition
    sakura:moveX(80, 1, true)

    -- Move the sprite to x=500 using an ease-out interpolation
    -- This animation will have a duration of 1 second and will be a non-blocking transition
    sakura:moveX(500, 1, false, Interpolator.easeOut)


See also
^^^^^^^^

* :doc:`move`
* :doc:`../../enums/interpolator`
* :doc:`setPosition`
* :doc:`setX`