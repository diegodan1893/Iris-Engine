The scene function
==================

:Syntax:
	| scene(*string* image, *number* time = 0.5)
	| scene(*string* image, *TransitionObject* transition)
:Returns: *nil*

This function hides all the objects in the scene and then changes the background to
the specified image.


Parameters
^^^^^^^^^^

+--------------------+------------+-----------------------------------------------------------------------------+
| Type               | Name       | Description                                                                 |
+====================+============+=============================================================================+
| *string*           | image      | Path to the image to use as the new background; see remarks_ for details    |
+--------------------+------------+-----------------------------------------------------------------------------+
| *number*           | time       | The duration in seconds of the default transition; see remarks_ for details |
+--------------------+------------+-----------------------------------------------------------------------------+
| *TransitionObject* | transition | :doc:`Transition<../enums/transition>` to use; see remarks_ for details     |
+--------------------+------------+-----------------------------------------------------------------------------+


Remarks
^^^^^^^

The path of the *image* parameter must be relative to the *backgrounds* path
specified in the :doc:`config<../../../config>` file.

If no :doc:`Transition<../enums/transition>` object is given, this one will be used
by default:

.. code-block:: lua

    {type=Transition.dissolve, time=0.5, block=true}

If the second argument of the function is a number, a *dissolve* transition will
be used. The number will determine the duration in seconds of the *dissolve*.

This function supports the following transition types:

* Transition.none
* Transition.dissolve
* Transition.imageDissolve
  
.. note::

	Scene transitions will always be :term:`blocking<blocking transition>`.


Examples
^^^^^^^^

.. code-block:: lua

    -- This will use a dissolve transition with a duration of 0.5 seconds
    scene("sky.png")

    -- This will use a dissolve transition with a duration of 1 second
    scene("sky.png", 1)

    -- This will use an imageDissolve transition with a duration of 1 second
    scene("sky.png", {type=Transition.imageDissolve, image="left.png", time=1})


See also
^^^^^^^^

* :doc:`setBackground`
* :doc:`../enums/transition`