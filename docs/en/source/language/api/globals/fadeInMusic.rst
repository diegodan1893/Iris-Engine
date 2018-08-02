The fadeInMusic function
========================

:Syntax: fadeInMusic(*string* music, *number* seconds)
:Returns: *nil*

Starts playing the specified sound file with a fade effect. The music will loop until
you start playing another file or call a function that stops it.

The fade-in effect only applies to the first loop.


Parameters
^^^^^^^^^^

+----------+---------+----------------------------------------------------------+
| Type     | Name    | Description                                              |
+==========+=========+==========================================================+
| *string* | music   | Path to the sound file to play; see remarks_ for details |
+----------+---------+----------------------------------------------------------+
| *number* | seconds | Seconds for the fade-in effect to complete               |
+----------+---------+----------------------------------------------------------+


Remarks
^^^^^^^

The path of the *music* parameter must be relative to the *music* path
specified in the :doc:`config<../../../config>` file.


Examples
^^^^^^^^

.. code-block:: lua

    -- Start playing BGM01.ogg with a fade-in effect of 3 seconds
    fadeInMusic("BGM01.ogg", 3)

    ...

    -- Stop the music with a fade
    fadeOutMusic(1)


See also
^^^^^^^^

* :doc:`playMusic`
* :doc:`stopMusic`
* :doc:`fadeOutMusic`