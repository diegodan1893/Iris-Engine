The setPosition method
======================

:Syntax:
	|	setPosition(*number* x, *number* y)
	|	setPosition(*Position* position)
:Returns: *nil*

This method is used to set the position of the character sprite.


Parameters
^^^^^^^^^^

+------------+----------+---------------------------------------------------------------------------------------------+
| Type       | Name     | Description                                                                                 |
+============+==========+=============================================================================================+
| *number*   | x        | Distance in pixels from the left side of the screen                                         |
+------------+----------+---------------------------------------------------------------------------------------------+
| *number*   | y        | Distance in pixels from the top of the screen                                               |
+------------+----------+---------------------------------------------------------------------------------------------+
| *Position* | position | The :doc:`Position<../../enums/position>` of the character sprite; see remarks_ for details |
+------------+----------+---------------------------------------------------------------------------------------------+


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
  
.. warning::
	While this method allows you to use non-integer coordinates, keep in mind that if
	a sprite is not aligned with the pixel grid it will look blurry due to anti-aliasing.


Examples
^^^^^^^^

.. code-block:: lua

    -- Define a character sprite that uses "sakura1.png" as the base image
    sakura = CharacterSprite.new("sakura1.png")

    -- Set its position to (29, 700)
    sakura:setPosition(29, 700)
    
    -- Set its position to the center of the screen
    sakura:setPosition(Position.center)


See also
^^^^^^^^

* :doc:`setX`
* :doc:`move`
* :doc:`moveX`