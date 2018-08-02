The playSound function
======================

:Syntax: playSound(*string* sound)
:Returns: *nil*

Plays the specified sound file once. There can be multiple sounds playing at the
same time.


Parameters
^^^^^^^^^^

+----------+-------+----------------------------------------------------------+
| Type     | Name  | Description                                              |
+==========+=======+==========================================================+
| *string* | sound | Path to the sound file to play; see remarks_ for details |
+----------+-------+----------------------------------------------------------+


Remarks
^^^^^^^

The path of the *sound* parameter must be relative to the *sounds* path
specified in the :doc:`config<../../../config>` file.


Examples
^^^^^^^^

.. code-block:: lua

    -- Play splash.ogg and surprise.ogg at the same time
    playSound("splash.ogg")
    playSound("surprise.ogg")


See also
^^^^^^^^

* :doc:`stopSound`