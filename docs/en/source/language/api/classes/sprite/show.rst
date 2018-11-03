The show method
===============

:Syntax: show([*TransitionObject* transition])
:Returns: *nil*

This method is used to make the sprite appear on the screen.


Parameters
^^^^^^^^^^

+--------------------+------------+---------------------------------------------------------------------------+
| Type               | Name       | Description                                                               |
+====================+============+===========================================================================+
| *TransitionObject* | transition | :doc:`Transition<../../enums/transition>` to use; se remarks_ for details |
+--------------------+------------+---------------------------------------------------------------------------+


Remarks
^^^^^^^

If no *transition* is given, this one will be used by default:

.. code-block:: lua

    {type=Transition.fade, time=0.3, block=false}

This method supports the following transition types:

* Transition.none
* Transition.fade


Examples
^^^^^^^^

.. code-block:: lua

    -- Create a Sprite object
    ball = Sprite.new("ball.png", 1)

    -- Make it appear on the screen with the default transition
    ball:show()

    ...

    -- Show the sprite using a blocking fade transition with a duration of 5 seconds
    ball:show({type=Transition.fade, time=5, block=true})


See also
^^^^^^^^

* :doc:`hide`
* :doc:`../../enums/transition`