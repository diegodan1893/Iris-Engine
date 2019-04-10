Text constructor
================

:Syntax: Text.new(*table* font, *number* zindex)

Constructs a Text object.

This object will be placed at coordinates (0, 0), and its origin will be the top
left corner.


Parameters
^^^^^^^^^^

+----------+--------+----------------------------------------------------------------------------+
| Type     | Name   | Description                                                                |
+==========+========+============================================================================+
| *table*  | font   | Properties of the font to use to render the text; see remarks_ for details |
+----------+--------+----------------------------------------------------------------------------+
| *number* | zindex | The z-index of this sprite                                                 |
+----------+--------+----------------------------------------------------------------------------+


Remarks
^^^^^^^

The *font* argument must be a table with the following fields:

+----------+----------------+---------------------------------------------------------------------------------------+
| Type     | Name           | Description                                                                           |
+==========+================+=======================================================================================+
| *string* | file           | Path to the font file                                                                 |
+----------+----------------+---------------------------------------------------------------------------------------+
| *number* | size           | The point size (based on 72 DPI) of the font                                          |
+----------+----------------+---------------------------------------------------------------------------------------+
| *table*  | color          | A table with the fields r, g, b and a (alpha) specifying the color of the text        |
+----------+----------------+---------------------------------------------------------------------------------------+
| *number* | shadowDistance | Distance in pixels of the drop shadow. If 0, no shadow will be drawn.                 |
+----------+----------------+---------------------------------------------------------------------------------------+
| *table*  | shadowColor    | A table with the fields r, g, b and a (alpha) specifying the color of the text shadow |
+----------+----------------+---------------------------------------------------------------------------------------+


Examples
^^^^^^^^

.. code-block:: lua

    -- Font properties
    font = {
        file = "assets/fonts/Roboto-Medium.ttf",
        size = 28,
        color = {r = 255, g = 255, b = 255, a = 255},
        shadowDistance = 0,
        shadowColor = {r = 0, g = 0, b = 0, a = 0}
    }

    -- Create text object
    text = Text.new(font, 1)

    -- Set the text and show the object
    text:setText("This is an example")
    text:show()


See also
^^^^^^^^

* :doc:`setText`
* :doc:`../sprite/top`