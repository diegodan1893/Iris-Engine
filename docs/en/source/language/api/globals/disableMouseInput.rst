The disableMouseInput function
==============================

:Syntax: disableMouseInput([*number* zindex])
:Returns: *nil*

After calling this function, :doc:`buttons<../classes/button/top>` and
:doc:`clickable maps<../classes/clickableMap/top>` will **not** accept mouse input.
This means that the associated *onMouseEnter*, *onMouseExit* and *onClick* events
will not be triggered even if the conditions are met.


Parameters
^^^^^^^^^^

+----------+--------+---------------------------------------------------------------------------------------+
| Type     | Name   | Description                                                                           |
+==========+========+=======================================================================================+
| *number* | zindex | Only objects below this z-index will not accept mouse input; see remarks_ for details |
+----------+--------+---------------------------------------------------------------------------------------+


Remarks
^^^^^^^

Regardless of whether or not the mouse input is enabled, the player will be able to
click to dismiss the text displayed on the :term:`text window`.

Mouse input will be disabled automatically during :doc:`scene<scene>` transitions.

If a z-index is provided, this function will only have an effect in objects that are
below that z-index. This is useful if you want to create a modal window, where the
rest of the screen remains visible but the player can only interact with the content
of said window.


Examples
^^^^^^^^

.. code-block:: lua

    disableMouseInput()

    say "Buttons and clickable maps will not accept mouse input."

    enableMouseInput()


See also
^^^^^^^^

* :doc:`enableMouseInput`
* :doc:`scene`