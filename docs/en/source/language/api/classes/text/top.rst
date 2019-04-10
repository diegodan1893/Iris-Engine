The Text class
==============

This class is used to display text on the screen outside of the :term:`text window`.

Objects of this class behave like :doc:`sprites<../sprite/top>`, which means you can use
methods like :doc:`move<../sprite/move>` to animate them.


Properties
^^^^^^^^^^

The Text class inherits all of the properties of
:doc:`the Sprite class <../sprite/top>`.


Member functions
^^^^^^^^^^^^^^^^

.. toctree::
    :hidden:

    constructor
    setText

.. table::
    :widths: 1 100

    +-----------------------------------+-------------------------+
    | Method                            | Description             |
    +===================================+=========================+
    | :doc:`(constructor)<constructor>` | Create a Text object    |
    +-----------------------------------+-------------------------+
    | :doc:`setText<setText>`           | Set the text to display |
    +-----------------------------------+-------------------------+

The Text class inherits all of the methods of
:doc:`the Sprite class <../sprite/top>` except *defineSpriteSheet* and *setFrame*.