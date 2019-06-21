The stop method
===============

:Syntax: stop()
:Returns: *nil*

Stops video playback and hides the video object.


Examples
^^^^^^^^

.. code-block:: lua

    -- Create video object
    local opening = Video.new("op.ogv", true, false, 1)

    -- Start playback
    opening:show({type=Transition.none})
    opening:play(false)

    -- Wait 5 seconds and stop the video
    sleep(5)
    opening:stop()


See also
^^^^^^^^

* :doc:`play`
* :doc:`waitUntilFinished`