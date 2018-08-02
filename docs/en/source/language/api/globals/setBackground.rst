The setBackground function
==========================

:Syntax: setBackground(*string* image [, *TransitionObject* transition])
:Returns: *nil*

This function is used to change the background image of the current scene.

Unlike the :doc:`scene<scene>` function, this has no effect on the rest of the objects
of the scene, which will remain visible.


Parameters
^^^^^^^^^^

+--------------------+------------+--------------------------------------------------------------------------+
| Type               | Name       | Description                                                              |
+====================+============+==========================================================================+
| *string*           | image      | Path to the image to use as the new background; see remarks_ for details |
+--------------------+------------+--------------------------------------------------------------------------+
| *TransitionObject* | transition | :doc:`Transition<../enums/transition>` to use; se remarks_ for details   |
+--------------------+------------+--------------------------------------------------------------------------+


Remarks
^^^^^^^

The path of the *image* parameter must be relative to the *backgrounds* path
specified in the :doc:`config<../../../config>` file.

If no *transition* is given, this one will be used by default:

.. code-block:: lua

    {type=Transition.dissolve, time=0.5, block=false}

This function supports the following transition types:

* Transition.none
* Transition.dissolve


Examples
^^^^^^^^

.. code-block:: lua

    -- Start with a sunset
    scene("street sunset.png")

    say "It's getting late."

    -- Slowly change the background to a night scene over the course of 400 seconds
    setBackground("street night.png", {type=Transition.dissolve, time=400, block=false})

    -- Continue with the script while the background changes
    say "I should hurry."


See also
^^^^^^^^

* :doc:`scene`
* :doc:`../enums/transition`