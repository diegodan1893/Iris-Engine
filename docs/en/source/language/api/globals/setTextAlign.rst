The setTextAlign function
=========================

:Syntax: setTextAlign(*Position* alignment)
:Returns: *nil*

This function is used to specify the horizontal alignment of text in the
:term:`text window`.


Parameters
^^^^^^^^^^

+------------+-----------+----------------------------------------------------------------------------------------------------------+
| Type       | Name      | Description                                                                                              |
+============+===========+==========================================================================================================+
| *Position* | alignment | A value from the :doc:`position<../enums/position>` enum indicating the horizontal alignment of the text |
+------------+-----------+----------------------------------------------------------------------------------------------------------+


Remarks
^^^^^^^

Calling this function will set the horizontal aligment immediately, so you might get
unwanted results if you don't change the text being displayed after doing so. To
avoid this, call this function just before displaying new text or while the
:term:`text window` is hidden.


Examples
^^^^^^^^

.. code-block:: lua

    setTextAlign(Position.center)
    say "\nApril 27, 11:37 AM\nDistrict Court - Defendant Lobby No. 5"
    hideText()
    setTextAlign(Position.left)


See also
^^^^^^^^

* :doc:`../enums/position`