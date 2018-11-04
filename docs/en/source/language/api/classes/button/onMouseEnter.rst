The onMouseEnter property
=========================

Sets a function to execute when the mouse enters this button.

If set to *nil*, this event will be disabled.


Examples
^^^^^^^^

.. code-block:: lua

    -- Create a button
    exit = Button.new("exit button.png", 50)
    exit:setPosition(0, 552)

    -- This function will be executed when the mouse enters the button
    -- In this case, we will close the game
    exit.onMouseEnter = function()
        -- Stop the music and fade to black
        fadeOutMusic(2)
        scene("black.png", 2)

        -- Quit the game
        exitGame()
    end

    -- Show the button so that the player can interact with it
    exit:show()


See also
^^^^^^^^

* :doc:`onMouseExit`
* :doc:`onClick`