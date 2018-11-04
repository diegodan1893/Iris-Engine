The enabled property
====================

Sets wheter the player is able to interact with this button.

If set to false, the button will visually indicate to the player that it's disabled.


Examples
^^^^^^^^

.. code-block:: lua

	-- Create a button
	exit = Button.new("exit button.png", 50)
	exit:setPosition(0, 552)

	-- Disable and show it
	exit.enabled = false
	exit:show()


See also
^^^^^^^^

* :doc:`constructor`