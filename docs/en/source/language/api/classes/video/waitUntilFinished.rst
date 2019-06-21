The waitUntilFinished method
============================

:Syntax: waitUntilFinished()
:Returns: *nil*

Blocks the execution of the script until the video has finished playing.

Calling this method after the video has finished playing will not have any effects.


Examples
^^^^^^^^

.. code-block:: lua

    -- Create video object
    local opening = Video.new("op.ogv", true, false, 1)

    -- Start playback
    opening:show({type=Transition.none})
    opening:play(false)

    -- Show some text to the player
    say "This text will be shown while the video is playing."
    hideText()

    -- Once the player has read the text, wait until the video finishes playing
    video:waitUntilFinished()


See also
^^^^^^^^

* :doc:`play`
* :doc:`stop`