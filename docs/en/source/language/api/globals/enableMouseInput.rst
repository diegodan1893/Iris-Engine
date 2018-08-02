The enableMouseInput function
=============================

:Syntax: enableMouseInput()
:Returns: *nil*

After calling this function, :doc:`buttons<../button>` and
:doc:`clickable maps<../clickableMap>` will accept mouse input. This means that
the associated *onMouseEnter*, *onMouseExit* and *onClick* events will be triggered
when the conditions are met.

Mouse input is enabled by default.


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

* :doc:`disableMouseInput`
* :doc:`scene`