The stopMusic function
======================

:Syntax: stopMusic()
:Returns: *nil*

Abruptly stops playback of music.


Examples
^^^^^^^^

.. code-block:: lua

    -- Start playing BGM01.ogg with a fade-in effect of 3 seconds
    fadeInMusic("BGM01.ogg", 3)

    ...

    -- Stop the music
    stopMusic()


See also
^^^^^^^^

* :doc:`playMusic`
* :doc:`fadeInMusic`
* :doc:`fadeOutMusic`