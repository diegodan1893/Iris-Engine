Sprite constructor
==================

:Syntax: Sprite.new(*string* image, *number* zindex)

Constructs a Sprite object using the provided image with the specified z-index.

This sprite will be placed at coordinates (0, 0), and its origin will be the top
left corner of the image.


Parameters
^^^^^^^^^^

+----------+--------+--------------------------------------------------------------+
| Type     | Name   | Description                                                  |
+==========+========+==============================================================+
| *string* | image  | Path to the image to use as sprite; see remarks_ for details |
+----------+--------+--------------------------------------------------------------+
| *number* | zindex | The z-index of this sprite                                   |
+----------+--------+--------------------------------------------------------------+


Remarks
^^^^^^^

The path of the *image* parameter must be relative to the *sprites* path specified in
the :doc:`config file<../../../config>`.


Examples
^^^^^^^^

.. code-block:: lua

    -- Create a Sprite object
    ball = Sprite.new("ball.png", 1)


See also
^^^^^^^^

* :doc:`show`
* :doc:`hide`