The enableSkip function
=======================

:Syntax: enableSkip()
:Returns: *nil*

After calling this function, holding the ``Ctrl`` key will quickly advance the
dialogue. In addition, the player will be able to skip
:term:`blocking transitions<blocking transition>` by pressing left mouse button, the
``Enter`` key or by rotating the mouse wheel.

*Skipping* is enabled by default.


Examples
^^^^^^^^

.. code-block:: lua

    disableSkip()

    say "The player will not be able to skip this text with the 'Ctrl' key."
    
    enableSkip()


See also
^^^^^^^^

* :doc:`disableSkip`