Video constructor
=================

:Syntax: Video.new(*string* file, *bool* playAudio, *bool* shouldLoop, *number* zindex)

Constructs a Video object.

This object will be placed at coordinates (0, 0), and its origin will be the top
left corner.

Videos will start buffering as soon as they are constructed. Try to allow some time for the
beginning of the video to buffer before starting playback to avoid stuttering. Half a second
is usually enough.


Parameters
^^^^^^^^^^

+----------+------------+-------------------------------------------------------------------------+
| Type     | Name       | Description                                                             |
+==========+============+=========================================================================+
| *string* | file       | Path to the video file; see remarks_ for details                        |
+----------+------------+-------------------------------------------------------------------------+
| *bool*   | playAudio  | Whether to play the audio track of this video; see remarks_ for details |
+----------+------------+-------------------------------------------------------------------------+
| *bool*   | shouldLoop | Whether the video should loop after it finishes playing                 |
+----------+------------+-------------------------------------------------------------------------+
| *number* | zindex     | The z-index of the video                                                |
+----------+------------+-------------------------------------------------------------------------+


Remarks
^^^^^^^

The path of the *file* parameter must be relative to the *videos* path
specified in the :doc:`config<../../../../config>` file.

If audio playback is enabled, the audio track of the video will replace the current
music, which will be paused while the video is playing. This does not affect other
sounds. It is not possible to play the audio track of more than one video at the same
time.

.. important::
    Audio bitrate must be 44100 kHz, otherwise the audio will sound distorted.


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

* :doc:`play`
* :doc:`stop`
* :doc:`../sprite/show`