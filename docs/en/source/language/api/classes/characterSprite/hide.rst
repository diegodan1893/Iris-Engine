The hide method
===============

:Syntax: hide([*TransitionObject* transition])
:Returns: *nil*

This method is used to make the character sprite disappear from the screen.


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

    -- Define a character sprite that uses "sakura1.png" as the base image
    sakura = CharacterSprite.new("sakura1.png")

    -- Make it visible with a smile expression
    sakura:show("smiling")
    say "I'm smiling now."

    -- Hide it using the default transition
    sakura:hide()


See also
^^^^^^^^

* :doc:`show`
* :doc:`../../enums/transition`