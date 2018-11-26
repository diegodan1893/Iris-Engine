The disableColorGrading method
==============================

:Syntax: disableColorGrading(*number* time)
:Returns: *nil*

Disable color grading effects for this character sprite.


Parameters
^^^^^^^^^^

+----------+------+---------------------------------------------------------+
| Type     | Name | Description                                             |
+==========+======+=========================================================+
| *number* | time | The duration in seconds of the color grading transition |
+----------+------+---------------------------------------------------------+


Remarks
^^^^^^^

Color grading transitions are always :term:`non-blocking<non-blocking transition>`.
If you call this method while a color grading transition is taking place, that
transition will be finished instantly before starting the new one.


Examples
^^^^^^^^

.. code-block:: lua

    -- Define a character sprite
    sakura = CharacterSprite.new("sakura1.png")

    -- Show a night background and the character sprite with color grading
    scene("street night.png")
    sakura:setColorLUT("night.png", 0)
    sakura:show("normal")
    say "Night."

    -- Change the background to a day setting at the same time
    -- disable color grading for our character
    setBackground("street day.png")
    sakura:disableColorGrading(0.5)
    say "Day."


See also
^^^^^^^^

* :doc:`setColorLut`