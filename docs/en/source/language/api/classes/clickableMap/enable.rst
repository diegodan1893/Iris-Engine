The enable method
=================

:Syntax: enable()
:Returns: *nil*

This method is used to allow the player to interact with a ClickableMap object.

If :doc:`the nonBlocking property<nonBlocking>` is set to ``false``, the execution of
the script will be paused until the clickable map is disabled.


Examples
^^^^^^^^

.. code-block:: lua

    -- Create a clickable map
    map = ClickableMap.new("drawers_map.png")

    ...

    -- Enable the clickable map
    map:enable()


See also
^^^^^^^^

* :doc:`disable`
* :doc:`nonBlocking`
* :doc:`disableOnClick`