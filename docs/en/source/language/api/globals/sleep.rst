The sleep function
==================

:Syntax: sleep(*number* seconds)
:Returns: *nil*

Pauses the execution of the script for the specified number of seconds. This is useful to create dramatic pauses, show an image that will stay on screen
for a certain amount of time, etc.

This pause will behave as a
:term:`blocking transition`, so the player can skip it by
clicking the mouse. This can be disabled with the :doc:`disableSkip<disableSkip>` function.


Parameters
^^^^^^^^^^

+----------+---------+-----------------------------------------------------+
| Type     | Name    | Description                                         |
+==========+=========+=====================================================+
| *number* | seconds | Number of seconds to wait; see remarks_ for details |
+----------+---------+-----------------------------------------------------+


Remarks
^^^^^^^

The sleep function will pause the execution of the script for *at least* the given
number of seconds. Depending on external circumnstances such as framerate or load,
the actual elapsed time might be longer.

The minimum ammount of time this function can wait is the time it takes to render a
frame, so calling ``sleep(0)`` will pause the execution of the script until the next
frame.


Examples
^^^^^^^^

.. code-block:: lua

    -- Fade to black, wait 1 second and show the next background
    scene("black.png")
    sleep(1)
    scene("sky.png")


See also
^^^^^^^^

* :doc:`yield`
* :doc:`disableSkip`