The Video class
===============

This class is used to play video files.

Objects of this class behave like :doc:`sprites<../sprite/top>`, which means you can use
methods like :doc:`move<../sprite/move>` to animate them.

.. important::
    Audio bitrate must be 44100 kHz, otherwise the audio will sound distorted.


Properties
^^^^^^^^^^

The Video class inherits all of the properties of
:doc:`the Sprite class <../sprite/top>`.


Member functions
^^^^^^^^^^^^^^^^

.. toctree::
    :hidden:

    constructor
    play
    stop
    waitUntilFinished

.. table::
    :widths: 1 100

    +---------------------------------------------+-------------------------------------------------------------------------+
    | Method                                      | Description                                                             |
    +=============================================+=========================================================================+
    | :doc:`(constructor)<constructor>`           | Create a Video object                                                   |
    +---------------------------------------------+-------------------------------------------------------------------------+
    | :doc:`play<play>`                           | Starts video playback                                                   |
    +---------------------------------------------+-------------------------------------------------------------------------+
    | :doc:`stop<stop>`                           | Stops video playback                                                    |
    +---------------------------------------------+-------------------------------------------------------------------------+
    | :doc:`waitUntilFinished<waitUntilFinished>` | Blocks the execution of the script until the video has finished playing |
    +---------------------------------------------+-------------------------------------------------------------------------+

The Video class inherits all of the methods of
:doc:`the Sprite class <../sprite/top>` except *defineSpriteSheet* and *setFrame*.