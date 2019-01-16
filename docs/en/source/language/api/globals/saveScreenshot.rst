The saveScreenshot function
===========================

:Syntax: saveScreenshot(*string* path, *number* width, *number* height)
:Returns: *nil*

Takes a screenshot of the game and saves it to a file.


Parameters
^^^^^^^^^^

+----------+--------+---------------------------------------------------+
| Type     | Name   | Description                                       |
+==========+========+===================================================+
| *string* | path   | Where to save the image; see remarks_ for details |
+----------+--------+---------------------------------------------------+
| *number* | width  | The width in pixels of the image to save          |
+----------+--------+---------------------------------------------------+
| *number* | height | The height in pixels of the image to save         |
+----------+--------+---------------------------------------------------+



Remarks
^^^^^^^

The screenshot will be stretched to fit the provided resolution.

The format of the image will be deduced from the extension of the provided
filename. Supported formats are: png, bmp and tga.


Examples
^^^^^^^^

.. code-block:: lua

	-- Save a screenshot as "screenshot.png"
	-- The resolution of the saved image will be 1280x720
	saveScreenshot("screenshot.png", 1280, 720)

