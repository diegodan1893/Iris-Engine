CharacterSprite constructor
===========================

:Syntax:
    | CharacterSprite.new(
    |   *string* baseImage,
    |   *Position* position = Position.center
    |   [, *number* zindex]
    | )
    | CharacterSprite.new(
    |   *string* baseImage,
    |   *table* positionVector,
    |   [, *number* zindex]
    | )

Constructs a CharacterSprite object.

The origin of character sprites is located at the bottom center of the sprite, as
this makes it easier to align them with the bottom of the screen.


Parameters
^^^^^^^^^^

+------------+----------------+---------------------------------------------------------------------------------------------+
| Type       | Name           | Description                                                                                 |
+============+================+=============================================================================================+
| *string*   | baseImage      | Path to the image to use as the base of the character sprite; see remarks_ for details      |
+------------+----------------+---------------------------------------------------------------------------------------------+
| *Position* | position       | The :doc:`Position<../../enums/position>` of the character sprite; see remarks_ for details |
+------------+----------------+---------------------------------------------------------------------------------------------+
| *table*    | positionVector | A vector with the position of the sprite; see remarks_ for details                          |
+------------+----------------+---------------------------------------------------------------------------------------------+
| *number*   | zindex         | The z-index of this character sprite; see remarks_ for details                              |
+------------+----------------+---------------------------------------------------------------------------------------------+


Remarks
^^^^^^^

The path of the *baseImage* parameter must be relative to the *characters* path
specified in the :doc:`config file<../../../config>`.

You can specify the position of the character sprite using
:doc:`the Position enum<../../enums/position>` or a *table*. If you use the
Position enum, the bottom of the character sprite will be aligned with the bottom
of the screen. Additionally:

* ``Position.left`` will align the left side of the character sprite with the left side of the screen
* ``Position.center`` will center the sprite horizontally
* ``Position.right`` will align the right side of the character sprite with the right side of the screen
  
Alternatively, you can use a *table* to specify the exact coordinates of your
character sprite. For example, if you want to place the sprite at coordinates
(100, 700), you can use the following table: ``{x=100, y=700}``. Keep in mind that
the origin of character sprites is located at the bottom center of the sprite.

If the *zindex* parameter is not specified, the engine will use the default z-index
for characters defined in the :doc:`config file<../../../config>`.


Examples
^^^^^^^^

.. code-block:: lua

    -- Define a character sprite that uses "sakura1.png" as the base image
    sakura = CharacterSprite.new("sakura1.png")

    -- Define a character sprite centered on the screen and with a z-index of 200
    sakura = CharacterSprite.new("sakura2.png", Position.center, 200)

    -- Define a character sprite using a table to set its position
    sakura = CharacterSprite.new("sakura2.png", {x=29, y=700})


See also
^^^^^^^^

* :ref:`Using character sprites<using-character-sprites>`
* :doc:`../../enums/position`
* :doc:`show`
* :doc:`hide`