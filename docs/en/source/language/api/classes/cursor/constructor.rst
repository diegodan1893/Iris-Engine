Cursor constructor
==================

:Syntax: Cursor.new(*string* image, *number* hotX, *number* hotY)

Constructs a Cursor object with the specified image.


Parameters
^^^^^^^^^^

+----------+-------+--------------------------------------------------------+
| Type     | Name  | Description                                            |
+==========+=======+========================================================+
| *string* | image | The path to the cursor image; see remarks_ for details |
+----------+-------+--------------------------------------------------------+
| *number* | hotX  | The x position of the cursor hot spot                  |
+----------+-------+--------------------------------------------------------+
| *number* | hotY  | The y position of the cursor hot spot                  |
+----------+-------+--------------------------------------------------------+


Remarks
^^^^^^^

The path of the *image* parameter must be relative to the *gui* path specified in
the :doc:`config file<../../../../config>`.


Examples
^^^^^^^^

.. code-block:: lua

	-- Create a mouse cursor
	pointer = Cursor.new("red arrow.png", 0, 0)

	-- Change the mouse cursor to the one we just created
	setCursor(pointer)

	...

	-- Restore the default system cursor
	setCursor(nil)


See also
^^^^^^^^

* :doc:`../../globals/setCursor`