The nonBlocking property
========================

By default, :doc:`the enable method<enable>` is a :term:`blocking function`, which
means that the execution of the script is paused until the clickable map is
disabled. However, if *nonBlocking* is set to ``true``, the execution of the script
will not be paused while the map is enabled.


Examples
^^^^^^^^

.. code-block:: lua

	-- Create a clickable map
	map = ClickableMap.new("drawers_map.png")

	-- Set nonBlocking to true
	map.nonBlocking = true


See also
^^^^^^^^

* :doc:`enable`
* :doc:`disable`