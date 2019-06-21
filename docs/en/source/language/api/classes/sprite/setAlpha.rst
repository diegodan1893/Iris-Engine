The setAlpha method
===================

:Syntax: setAlpha(*number* alpha)
:Returns: *nil*

Sets the opacity of the sprite.


Parameters
^^^^^^^^^^

+----------+-------+------------------------------------------------------------------------------------------------+
| Type     | Name  | Description                                                                                    |
+==========+=======+================================================================================================+
| *number* | alpha | A number in the range [0, 255], where 0 is completely transparent and 255 the original opacity |
+----------+-------+------------------------------------------------------------------------------------------------+


Remarks
^^^^^^^

If alpha is greater than 0, the sprite will be made visible.

Calling this function will skip any fade transition currently taking place for this
sprite.

Calling :doc:`show<show>` or :doc:`hide<hide>` will restore the alpha value to 255.


Examples
^^^^^^^^

.. code-block:: lua

    -- Create a Sprite object
    ball = Sprite.new("ball.png", 1)

    -- Set the alpha to 100
    ball:setAlpha(100)


See also
^^^^^^^^

* :doc:`show`
* :doc:`hide`