The show method
===============

:Syntax: show(*string* expression [, *TransitionObject* transition])
:Returns: *nil*

This method is used to change the expression of the character sprite. If the sprite
was not visible, this method will make it visible.


Parameters
^^^^^^^^^^

+--------------------+------------+---------------------------------------------------------------------------+
| Type               | Name       | Description                                                               |
+====================+============+===========================================================================+
| *string*           | expression | The facial expression of the characer sprite; see remarks_ for details    |
+--------------------+------------+---------------------------------------------------------------------------+
| *TransitionObject* | transition | :doc:`Transition<../../enums/transition>` to use; se remarks_ for details |
+--------------------+------------+---------------------------------------------------------------------------+


Remarks
^^^^^^^

If the expression base for this character is ``sakura1.png`` and the provided
*expression* is ``smiling``, the expression image that will be drawn is
``sakura1 smiling.png``. In this example, the name of the base image and the name
of the expression have been connected with a space character to form the final
filename of the expression image, but you can alter this behavior in the
:doc:`config file<../../../config>`.

If no *transition* is given, these ones will be used by default:

.. code-block:: lua

    -- If the character sprite was not visible
    {type=Transition.fade, time=0.3, block=false}

    -- If the character sprite was visible
    {type=Transition.dissolve, time=0.3, block=false}

This method supports the following transition types:

* Transition.none
* Transition.fade (if the character sprite is not visible)
* Transition.dissolve (if the character sprite is visible)


Examples
^^^^^^^^

.. code-block:: lua

    -- Define a character sprite that uses "sakura1.png" as the base image
    sakura = CharacterSprite.new("sakura1.png")

    -- Make it visible with a smile expression
    sakura:show("smiling")
    say "I'm smiling now."

    -- Change the expression of the character sprite while it's visible
    sakura:show("normal")
    say "And this is my neutral expression."

    -- Change the expression using a blocking dissolve transition
    sakura:show("laughing", {type=Transition.dissolve, time=0.3, block=true})
    say "And now I'm laughing."


See also
^^^^^^^^

* :doc:`hide`
* :doc:`setExpressionBase`
* :doc:`setBase`
* :doc:`../../enums/transition`