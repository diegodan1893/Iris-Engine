The exitGame function
=====================

:Syntax: exitGame()
:Returns: This function does not return

Calling this function will immediately close the game. 


Examples
^^^^^^^^

.. code-block:: lua

    -- Create a button to quit the game
    local closeBtn = Button.new("closeBtn.png", 50)
    closeBtn:setPosition(0, 552)

    -- The function to call when the user presses the button
    closeBtn.onClick = function()
    	-- Fade to black and stop the music
    	fadeOutMusic(2)
    	scene("black.png", 2)

    	-- Quit the game
    	exitGame()
    end

    -- Show the button so that the player can press it
    closeBtn:show()

