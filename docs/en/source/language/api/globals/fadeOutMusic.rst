The fadeOutMusic function
=========================

:Syntax: fadeOutMusic(*number* seconds)
:Returns: *nil*

Gradually fade out the music over the specified seconds.


Parameters
^^^^^^^^^^

+----------+---------+---------------------------------------------+
| Type     | Name    | Description                                 |
+==========+=========+=============================================+
| *number* | seconds | Seconds for the fade-out effect to complete |
+----------+---------+---------------------------------------------+


Examples
^^^^^^^^

.. code-block:: lua

    -- Start playing BGM01.ogg with a fade-in effect of 3 seconds
    fadeInMusic("BGM01.ogg", 3)

    ...

    -- Stop the music with a fade-out effect of 1 second
    fadeOutMusic(1)


See also
^^^^^^^^

* :doc:`playMusic`
* :doc:`fadeInMusic`
* :doc:`stopMusic`