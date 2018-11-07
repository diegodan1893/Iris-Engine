The setExpressionBase method
============================

:Syntax: setExpressionBase(*string* expressionBase)
:Returns: *nil*

Let's say you have a base image called "sakura3.png" that should use the same expression
images as "sakura2.png". The setExpressionBase method allows you to do that.


Parameters
^^^^^^^^^^

+----------+----------------+---------------------------------------------------------------------------+
| Type     | Name           | Description                                                               |
+==========+================+===========================================================================+
| *string* | expressionBase | The base image of the set of expressions to use; see remarks_ for details |
+----------+----------------+---------------------------------------------------------------------------+


Remarks
^^^^^^^

The path of the *expressionBase* parameter must be relative to the *characters* path
specified in the :doc:`config file<../../../config>`.

The *expressionBase* parameter specifies the base image used when constructing the
filenames of expression images, allowing you to use the set of expressions
corresponding to a different base image than the one you want to use to draw the
character.

.. error::
	Using this method while the character sprite is visible will result in an error.


Examples
^^^^^^^^

.. code-block:: lua

    -- Define a character sprite that uses "sakura2.png" as the base image
    sakura = CharacterSprite.new("sakura2.png")

    -- Set "sakura1.png" as the expression base
    sakura:setExpressionBase("sakura1.png")

    -- Show the character sprite using "sakura2.png" as the base image
    -- and "sakura1 smiling.png" as the expression image
    sakura:show("smiling")


See also
^^^^^^^^

* :doc:`show`
* :doc:`setBase`
* :ref:`Using character sprites<using-character-sprites>`