The skipTransition function
===========================

:Syntax: skipTransition()
:Returns: *nil*

This method is used to instantly finish any transitions currently affecting this
object, including fades and movement animations started with
:doc:`the move method<move>`.


Remarks
^^^^^^^

As :term:`blocking transitions<blocking transition>` pause the execution of the
script, it is only possible to skip
:term:`non-blocking transitions<non-blocking transition>` using this method.


Examples
^^^^^^^^

.. code-block:: lua

	-- Define a character sprite that uses "sakura1.png" as the base image
	sakura = CharacterSprite.new("sakura1.png")

	-- Make it visible with a smile expression
	sakura:show("smiling")

	-- Start a non blocking movement animation with a duration of 10 seconds
	sakura:moveX(0, 10, false)

	-- Wait 5 seconds
	sleep(5)

	-- Instantly finish the animation
	sakura:skipTransition()


See also
^^^^^^^^

* :doc:`move`
* :doc:`moveX`
* :doc:`show`
* :doc:`hide`