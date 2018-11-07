The setBase method
==================

:Syntax: 
    |   setBase(
    |       *string* baseImage,
    |       *string* expressionBase,
    |       *string* expression
    |       [, *TransitionObject* transition]
    |   )
:Returns: *nil*

This methods allows you to change the base image of a character sprite at any time,
even if it's visible.

.. note::
    In the current version of the engine, the new base image must have the same
    resolution as the previous one, otherwise one of the images will be stretched
    during the transition.


Parameters
^^^^^^^^^^

+--------------------+----------------+----------------------------------------------------------------------------------------+
| Type               | Name           | Description                                                                            |
+====================+================+========================================================================================+
| *string*           | baseImage      | Path to the image to use as the base of the character sprite; see remarks_ for details |
+--------------------+----------------+----------------------------------------------------------------------------------------+
| *string*           | expressionBase | The base image of the set of expressions to use; see remarks_ for details              |
+--------------------+----------------+----------------------------------------------------------------------------------------+
| *string*           | expression     | The facial expression of the characer sprite; see remarks_ for details                 |
+--------------------+----------------+----------------------------------------------------------------------------------------+
| *TransitionObject* | transition     | :doc:`Transition<../../enums/transition>` to use; se remarks_ for details              |
+--------------------+----------------+----------------------------------------------------------------------------------------+


Remarks
^^^^^^^

The path of the *baseImage* and *expressionBase* parameters must be relative to the
*characters* path specified in the :doc:`config file<../../../config>`.

The base image that will be drawn is the one specified in the *baseImage* parameter.
The *expressionBase* parameter specifies the base image used when constructing the
filenames of expression images, allowing you to use the set of expressions
corresponding to a different base image than the one you want to use to draw the
character.

If the *expressionBase* is ``sakura1.png`` and the provided *expression* is
``smiling``, the expression image that will be drawn is ``sakura1 smiling.png``.
In this example, the name of the base and the name of the expression have been
connected using a space character to form the final filename of the expression
image. This behavior can be altered in the :doc:`config file<../../../config>`.

If no *transition* is given, this one will be used by default:

.. code-block:: lua

    {type=Transition.dissolve, time=0.3, block=false}

This method supports the following transition types:

* Transition.none
* Transition.dissolve
  
If the character sprite is not visible, the *transition* parameter will be
ignored.


Examples
^^^^^^^^

.. code-block:: lua

    -- Define a character sprite that uses sakura2.png as the base image
    sakura = CharacterSprite.new("sakura2.png")
    sakura:show("smiling")

    ...

    -- Change the base to sakura3.png but keep using the set of expressions of sakura2.png
    sakura:setBase("sakura3.png", "sakura2.png", "smiling")

    -- Do the same using a blocking dissolve transition
    sakura:setBase("sakura3.png", "sakura2.png", "smiling", {type=Transition.dissolve, time=0.3, block=true})


See also
^^^^^^^^

* :doc:`show`
* :doc:`setExpressionBase`
* :doc:`../../enums/transition`
* :ref:`Using character sprites<using-character-sprites>`