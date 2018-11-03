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

	-- Create a Sprite object and show it
	ball = Sprite.new("ball.png", 1)
	ball:show()

	-- Start a non blocking movement animation with a duration of 10 seconds
	ball:move(1000, 0, 10, false)

	-- Wait 5 seconds
	sleep(5)

	-- Instantly finish the animation
	ball:skipTransition()


See also
^^^^^^^^

* :doc:`move`
* :doc:`show`
* :doc:`hide`