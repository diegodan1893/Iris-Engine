The CharacterSprite class
=========================

The CharacterSprite class is used to display images of your characters on the screen.
It offers functionality to make showing the characters of your games with different
expressions easier.

See :ref:`Working with visuals<using-character-sprites>` for an explanation on how
to use them.


Member functions
^^^^^^^^^^^^^^^^

.. toctree::
    :hidden:

    constructor
    show
    hide
    setBase
    setColorLut
    disableColorGrading
    skipTransition
    setPosition
    setX
    move
    moveX
    setExpressionBase

.. table::
    :widths: 1 100

    +-------------------------------------------------+--------------------------------------------------------------------------------------------+
    | Method                                          | Description                                                                                |
    +=================================================+============================================================================================+
    | :doc:`(constructor)<constructor>`               | Create a CharacterSprite object                                                            |
    +-------------------------------------------------+--------------------------------------------------------------------------------------------+
    | :doc:`show<show>`                               | Change the expression of a character and make it visible                                   |
    +-------------------------------------------------+--------------------------------------------------------------------------------------------+
    | :doc:`hide<hide>`                               | Make the character sprite invisible                                                        |
    +-------------------------------------------------+--------------------------------------------------------------------------------------------+
    | :doc:`setBase<setBase>`                         | Set the base image of the character sprite                                                 |
    +-------------------------------------------------+--------------------------------------------------------------------------------------------+
    | :doc:`setColorLut<setColorLut>`                 | Set the color LUT to use for color grading                                                 |
    +-------------------------------------------------+--------------------------------------------------------------------------------------------+
    | :doc:`disableColorGrading<disableColorGrading>` | Disable color grading for this character sprite                                            |
    +-------------------------------------------------+--------------------------------------------------------------------------------------------+
    | :doc:`skipTransition<skipTransition>`           | Instantly finish any transition affecting this object                                      |
    +-------------------------------------------------+--------------------------------------------------------------------------------------------+
    | :doc:`setPosition<setPosition>`                 | Set the position of the sprite                                                             |
    +-------------------------------------------------+--------------------------------------------------------------------------------------------+
    | :doc:`setX<setX>`                               | Set the position of the sprite while aligning it with the bottom of the screen             |
    +-------------------------------------------------+--------------------------------------------------------------------------------------------+
    | :doc:`move<move>`                               | Start a movement animation                                                                 |
    +-------------------------------------------------+--------------------------------------------------------------------------------------------+
    | :doc:`moveX<moveX>`                             | Start a movement animation where the end position is aligned with the bottom of the screen |
    +-------------------------------------------------+--------------------------------------------------------------------------------------------+
    | :doc:`setExpressionBase<setExpressionBase>`     | Set the base image that will be used when searching for expression images                  |
    +-------------------------------------------------+--------------------------------------------------------------------------------------------+
