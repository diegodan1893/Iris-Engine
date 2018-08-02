The hideText function
=====================

:Syntax: hideText()
:Returns: *nil*

This function is used to hide the :term:`text window` with the transition specified in
the :doc:`config file<../../config>`. This will always be a
:term:`blocking transition`.

It is usually called before the transition to a new :doc:`scene<scene>`.


Remarks
^^^^^^^

The :term:`text window` will remain hidden until new dialogue is displayed by using
the :doc:`say<say>` function or a :doc:`Character<../character>` object.


Examples
^^^^^^^^

.. code-block:: lua

    say "It's getting late."

    -- Hide the text window
    hideText()

    -- Change the scene
    scene("sky sunset.png")

    -- Show the text window again
    say "I should hurry."


See also
^^^^^^^^

* :doc:`say`
* :doc:`../character`