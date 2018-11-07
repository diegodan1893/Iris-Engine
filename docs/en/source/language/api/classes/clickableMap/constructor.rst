ClickableMap constructor
========================

:Syntax: ClickableMap.new(*string* image)

Constructs a ClickableMap object with the specified image.


Parameters
^^^^^^^^^^

+----------+-------+--------------------------------------------------------------------+
| Type     | Name  | Description                                                        |
+==========+=======+====================================================================+
| *string* | image | Path to the image describing the regions; see remarks_ for details |
+----------+-------+--------------------------------------------------------------------+


Remarks
^^^^^^^

The path of the *image* parameter must be relative to the *gui* path specified in
the :doc:`config file<../../../config>`.

In this image, each region must be represented using a different color. All of the
pixels of the image with the same color will be considered part of the same region.

This image must have the same resolution as the window of your game. The pixels
outside the window of the game are considered as black: *rgb(0, 0, 0)*.

.. warning::
    Make sure your drawing program does not apply anti-aliasing to the border of the
    regions of the image, as this will alter the color of the pixels around the
    borders and will cause problems.

.. important::
    Save your images in PNG, BMP or any other image format with **lossless**
    compression. JPEG is **NOT** suitable for this type of images as the compression
    can alter the color of the regions.


Examples
^^^^^^^^

.. code-block:: lua

	-- Create a clickable map
	map = ClickableMap.new("drawers_map.png")


See also
^^^^^^^^

* :doc:`How to use clickable maps<top>`
* :doc:`enable`