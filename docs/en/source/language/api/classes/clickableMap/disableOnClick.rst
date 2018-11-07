The disableOnClick property
===========================

If set to ``true``, the clickable map will be disabled automatically when the player
clicks on a region. This will prevent the player from clicking on another region
while the function for that region is being executed.

The clickable map will only be disabled if there is a function associated with the
region the player clicked.


Examples
^^^^^^^^

.. code-block:: lua

	-- Create a clickable map
	map = ClickableMap.new("drawers_map.png")

	-- Set disableOnClick to false
	map.disableOnClick = false


See also
^^^^^^^^

* :doc:`enable`
* :doc:`disable`
* :doc:`setOnClick`