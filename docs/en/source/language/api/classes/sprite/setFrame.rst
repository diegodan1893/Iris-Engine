The setFrame method
===================

:Syntax: setFrame(*number* frame)
:Returns: *nil*

If this object has been defined as a sprite sheet using
:doc:`defineSpriteSheet<defineSpriteSheet>`, this method can be used to manually set
the current frame of the animation.

This is more useful when the framerate of the animation is ``0``.


Parameters
^^^^^^^^^^

+----------+-------+----------------------------------------------------------------------------------------------+
| Type     | Name  | Description                                                                                  |
+==========+=======+==============================================================================================+
| *number* | image | The index of the frame to display, should be an integer in the range [0, NumberOfFrames - 1] |
+----------+-------+----------------------------------------------------------------------------------------------+


Examples
^^^^^^^^

.. code-block:: lua

    -- We have a sprite sheet where each frame contains a number from 0 to 9
    counter = Sprite.new("numbers.png", 1)
    counter:defineSpriteSheet(10, 10, 1, 0)

    -- With setFrame, we can display the digit we want
    -- Display the number 3
    counter:setFrame(3)


See also
^^^^^^^^

* :doc:`defineSpriteSheet`