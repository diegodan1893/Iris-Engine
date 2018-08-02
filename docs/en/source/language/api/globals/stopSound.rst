The stopSound function
======================

:Syntax: stopSound(*string* sound)
:Returns: *nil*

Stops all sounds that were loaded using the specified path.

If the :doc:`playSound<playSound>` function is called multiple times with the same
argument, the same sound can be played more than once at the same time. The stopSound
function will stop all of them.


Parameters
^^^^^^^^^^

+----------+-------+----------------------------------------------------------+
| Type     | Name  | Description                                              |
+==========+=======+==========================================================+
| *string* | sound | Path to the sound file to stop; see remarks_ for details |
+----------+-------+----------------------------------------------------------+


Remarks
^^^^^^^

The path of the *sound* parameter must be relative to the *sounds* path
specified in the :doc:`config<../../../config>` file.


Examples
^^^^^^^^

.. code-block:: lua

    -- Play sound
    playSound("people talking.ogg")

    say "There is a lot of noise here."

    -- Stop the sound
    stopSound("people talking.ogg")

    -- This dialogue will be shown at the same time the sound stops
    say "Silence, please."


See also
^^^^^^^^

* :doc:`playSound`