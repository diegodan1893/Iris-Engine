The Sprite class
================

The Sprite class is used to display images on the screen. See
:ref:`Working with visuals<using-sprites>` for a quick explanation on how to use
them.


Properties
^^^^^^^^^^

.. toctree::
    :hidden:

    visible

.. table::
    :widths: 1 1 1 100

    +--------+-------------------------+---------------+-----------------------------------------------------------------------+
    | Type   | Name                    | Default value | Description                                                           |
    +========+=========================+===============+=======================================================================+
    | *bool* | :doc:`visible<visible>` | *false*       | Gets whether or not the sprite is currently being shown in the screen |
    +--------+-------------------------+---------------+-----------------------------------------------------------------------+


Member functions
^^^^^^^^^^^^^^^^

.. toctree::
    :hidden:

    constructor
    show
    hide
    skipTransition
    setPosition
    getPosition
    setOrigin
    move
    defineSpriteSheet
    setFrame

.. table::
    :widths: 1 100

    +---------------------------------------------+--------------------------------------------------------------+
    | Method                                      | Description                                                  |
    +=============================================+==============================================================+
    | :doc:`(constructor)<constructor>`           | Create a Sprite object                                       |
    +---------------------------------------------+--------------------------------------------------------------+
    | :doc:`show<show>`                           | Make the sprite visible                                      |
    +---------------------------------------------+--------------------------------------------------------------+
    | :doc:`hide<hide>`                           | Make the sprite invisible                                    |
    +---------------------------------------------+--------------------------------------------------------------+
    | :doc:`skipTransition<skipTransition>`       | Instantly finish any transition affecting this object        |
    +---------------------------------------------+--------------------------------------------------------------+
    | :doc:`setPosition<setPosition>`             | Set the position of the sprite                               |
    +---------------------------------------------+--------------------------------------------------------------+
    | :doc:`getPosition<getPosition>`             | Get the position of the sprite                               |
    +---------------------------------------------+--------------------------------------------------------------+
    | :doc:`setOrigin<setOrigin>`                 | Set the origin of the sprite                                 |
    +---------------------------------------------+--------------------------------------------------------------+
    | :doc:`move<move>`                           | Start a movement animation                                   |
    +---------------------------------------------+--------------------------------------------------------------+
    | :doc:`defineSpriteSheet<defineSpriteSheet>` | Animate this sprite as a sprite sheet                        |
    +---------------------------------------------+--------------------------------------------------------------+
    | :doc:`setFrame<setFrame>`                   | Manually set the current frame of the sprite sheet animation |
    +---------------------------------------------+--------------------------------------------------------------+
