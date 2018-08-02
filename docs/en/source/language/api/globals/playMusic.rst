The playMusic function
======================

:Syntax: playMusic(*string* music)
:Returns: *nil*

Starts playing the specified sound file. The music will loop until you start playing
another file or call a function that stops it.


Parameters
^^^^^^^^^^

+----------+-------+----------------------------------------------------------+
| Type     | Name  | Description                                              |
+==========+=======+==========================================================+
| *string* | music | Path to the sound file to play; see remarks_ for details |
+----------+-------+----------------------------------------------------------+


Remarks
^^^^^^^

The path of the *music* parameter must be relative to the *music* path
specified in the :doc:`config<../../../config>` file.


Examples
^^^^^^^^

.. code-block:: lua

    -- Start playing BGM01.ogg
    playMusic("BGM01.ogg")

    ...

    -- Stop the music with a fade
    fadeOutMusic(1)


See also
^^^^^^^^

* :doc:`stopMusic`
* :doc:`fadeInMusic`
* :doc:`fadeOutMusic`