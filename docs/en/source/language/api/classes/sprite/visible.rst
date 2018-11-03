The visible property
====================

Gets whether or not the sprite is currently visible on the screen.


Examples
^^^^^^^^

.. code-block:: lua

    -- Create a Sprite object
    ball = Sprite.new("ball.png", 1)
    --> ball.visible is 'false'
    
    -- Show the sprite
    ball:show()
    --> ball.visible is 'true'
    
    -- Hide the sprite
    ball:hide({type=Transition.fade, time=0.3, block=true})
    --> ball.visible is 'false' after the transition has finished


See also
^^^^^^^^

* :doc:`show`
* :doc:`hide`