The precacheImage function
==========================

:Syntax: precacheImage(*string* image)
:Returns: *nil*

Iris Engine will load assets the first time they are needed. However, as loading
takes time, this can cause framerate drops during gameplay. To avoid this, you can
enable **precaching** in the :doc:`config<../../../config>` file, which will make
the engine preload images automatically when any object that uses them is defined.

There are, however, some images that will never be preloaded automatically, such as
character expressions. In cases where this is an issue, you can use the precacheImage
function to manually preload any image.

Keep in mind that preloading doesn't remove the framerate drop, it just makes it
easier to hide. Use this function just before a call to :doc:`sleep<sleep>` or
:doc:`yield<yield>` and the player won't be able to notice the drop.


Parameters
^^^^^^^^^^

+----------+-------+------------------------------+
| Type     | Name  | Description                  |
+==========+=======+==============================+
| *string* | image | Path to the image to preload |
+----------+-------+------------------------------+


Remarks
^^^^^^^

If precaching is enabled, there is usually no need to use this function. It's here in
case you observe performance issues during playtesting.


Examples
^^^^^^^^

.. code-block:: lua

    -- Fade to black
    scene("black.png")

    -- Take advantage of the scene transition to preload some images
    precacheImage("assets/images/characters/sakura2.png")
    precacheImage("assets/images/characters/sakura2 smiling.png")

    -- Wait 1 second before showing the next background
    sleep(1)
    scene("sky.png")


See also
^^^^^^^^

* :doc:`sleep`
* :doc:`yield`
* :doc:`../../../config`