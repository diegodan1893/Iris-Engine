The Text class
==============

This class is used to display text on the screen outside of the :term:`text window`.

Objects of this class behave like :doc:`sprites<../sprite/top>`, which means you can use
methods like :doc:`move<../sprite/move>` to animate them.


Properties
^^^^^^^^^^

.. toctree::
    :hidden:

    ellipsis
    spacing

.. table::
    :widths: 1 1 1 100

    +----------+---------------------------+---------------+------------------------------------------------------------+
    | Type     | Name                      | Default value | Description                                                |
    +==========+===========================+===============+============================================================+
    | *string* | :doc:`ellipsis<ellipsis>` | "..."         | Sets the ellipsis string to use when the text is truncated |
    +----------+---------------------------+---------------+------------------------------------------------------------+
    | *number* | :doc:`spacing<spacing>`   | 0             | Sets the spacing of the lines                              |
    +----------+---------------------------+---------------+------------------------------------------------------------+

The Text class inherits all of the properties of
:doc:`the Sprite class <../sprite/top>`.


Member functions
^^^^^^^^^^^^^^^^

.. toctree::
    :hidden:

    constructor
    setText
    setMaxSize
    getCurrentTextSize

.. table::
    :widths: 1 100

    +-----------------------------------------------+----------------------------------------------------+
    | Method                                        | Description                                        |
    +===============================================+====================================================+
    | :doc:`(constructor)<constructor>`             | Create a Text object                               |
    +-----------------------------------------------+----------------------------------------------------+
    | :doc:`setText<setText>`                       | Set the text to display                            |
    +-----------------------------------------------+----------------------------------------------------+
    | :doc:`setMaxSize<setMaxSize>`                 | Set the maximum size of the text box               |
    +-----------------------------------------------+----------------------------------------------------+
    | :doc:`getCurrentTextSize<getCurrentTextSize>` | Get the size of the text currently being displayed |
    +-----------------------------------------------+----------------------------------------------------+

The Text class inherits all of the methods of
:doc:`the Sprite class <../sprite/top>` except *defineSpriteSheet* and *setFrame*.