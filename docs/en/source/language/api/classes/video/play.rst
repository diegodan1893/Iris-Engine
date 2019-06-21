The play method
===============

:Syntax: play(*bool* shouldBlock)
:Returns: *nil*

Starts video playback.

.. tip::
	Use the :doc:`show<../sprite/show>` method to make the video visible before starting
	playback.


Parameters
^^^^^^^^^^

+--------+-------------+------------------------------------------------------------------------+
| Type   | Name        | Description                                                            |
+========+=============+========================================================================+
| *bool* | shouldBlock | Whether to block script execution until the video has finished playing |
+--------+-------------+------------------------------------------------------------------------+


Remarks
^^^^^^^

If audio playback is enabled, the audio track of the video will replace the current
music, which will be paused while the video is playing. This does not affect other
sounds. It is not possible to play the audio track of more than one video at the same
time.

.. important::
    Audio bitrate must be 44100 kHz, otherwise the audio will sound distorted.

The video will be hidden automatically when it finishes playing.


Examples
^^^^^^^^

.. code-block:: lua

    -- Create video object
    -- We want to play the video with sound, and we only want it to play once
    local opening = Video.new("op.ogv", true, false, 1)

    -- Make some time so that the video can buffer before we start playing it
    say "This is the opening of the game."
    hideText()

    -- Show the video
    opening:show({type=Transition.none})

    -- Start playback
    opening:play(true)


See also
^^^^^^^^

* :doc:`stop`
* :doc:`waitUntilFinished`
* :doc:`../sprite/show`