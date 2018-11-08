The setCursor function
======================

:Syntax: setCursor(*Cursor* cursor)
:Returns: *nil*

This function is used to change the mouse cursor.


Parameters
^^^^^^^^^^

+----------+--------+------------------------------------------------------------------------+
| Type     | Name   | Description                                                            |
+==========+========+========================================================================+
| *Cursor* | cursor | The new :doc:`Cursor<../classes/cursor/top>`; see remarks_ for details |
+----------+--------+------------------------------------------------------------------------+


Remarks
^^^^^^^

Passing *nil* as the argument will change the cursor to the default system cursor.


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

* :doc:`../classes/cursor/top`