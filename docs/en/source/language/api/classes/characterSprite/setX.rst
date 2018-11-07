The setX method
===============

:Syntax: setX(*number* x)
:Returns: *nil*

Most of the time you will only need to move the character sprite horizontally.
This method allows you to set the ``x`` position of the sprite, while the ``y``
position will be automatically calculated so that the bottom of the sprite is
aligned with the bottom of the screen.


Parameters
^^^^^^^^^^

+----------+------+-----------------------------------------------------+
| Type     | Name | Description                                         |
+==========+======+=====================================================+
| *number* | x    | Distance in pixels from the left side of the screen |
+----------+------+-----------------------------------------------------+


Remarks
^^^^^^^

The exact pixel of the image that lands in the provided position is called the
**origin**. The origin of character sprites is located at the bottom center of the
sprite.


Examples
^^^^^^^^

.. code-block:: lua

    -- Define a character sprite that uses "sakura1.png" as the base image
    sakura = CharacterSprite.new("sakura1.png")

    -- Set its horizontal position
    sakura:setX(100)


See also
^^^^^^^^

* :doc:`setPosition`
* :doc:`move`
* :doc:`moveX`