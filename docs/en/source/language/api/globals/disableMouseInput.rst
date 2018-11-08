The disableMouseInput function
==============================

:Syntax: disableMouseInput()
:Returns: *nil*

After calling this function, :doc:`buttons<../classes/button/top>` and
:doc:`clickable maps<../classes/clickableMap/top>` will **not** accept mouse input.
This means that the associated *onMouseEnter*, *onMouseExit* and *onClick* events
will not be triggered even if the conditions are met.


Remarks
^^^^^^^

Regardless of whether or not the mouse input is enabled, the player will be able to
click to dismiss the text displayed on the :term:`text window`.

Mouse input will be disabled automatically during :doc:`scene<scene>` transitions.


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