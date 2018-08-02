The disableSkip function
========================

:Syntax: disableSkip()
:Returns: *nil*

After calling this function, holding the ``Ctrl`` key will not skip the
dialogue. In addition, the player will not be able to skip
:term:`blocking transitions<blocking transition>`.


Examples
^^^^^^^^

.. code-block:: lua

    disableSkip()

    say "The player will not be able to skip this text with the 'Ctrl' key."
    
    enableSkip()


See also
^^^^^^^^

* :doc:`enableSkip`