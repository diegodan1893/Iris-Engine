API reference index
===================

Here you will find detailed information about all the functions, classes and
enumerations you can use in your scripts.



Functions
=========

.. toctree::
    :hidden:

    globals/say
    globals/append
    globals/hideText
    globals/setTextAlign
    globals/setBackground
    globals/scene
    globals/disableSkip
    globals/enableSkip
    globals/disableMouseInput
    globals/enableMouseInput
    globals/getMousePosition
    globals/setCursor
    globals/setOnRightClick
    globals/playMusic
    globals/fadeInMusic
    globals/stopMusic
    globals/fadeOutMusic
    globals/playSound
    globals/stopSound
    globals/yield
    globals/sleep
    globals/getDeltaSeconds
    globals/openScript
    globals/exitGame
    globals/saveScreenshot
    globals/precacheImage

**Narration**

.. table::
    :widths: 1 100

    +-------------------------------------------+------------------------------------------+
    | Function                                  | Description                              |
    +===========================================+==========================================+
    | :doc:`say<globals/say>`                   | Display narration text                   |
    +-------------------------------------------+------------------------------------------+
    | :doc:`append<globals/append>`             | Add text to the currently displayed line |
    +-------------------------------------------+------------------------------------------+
    | :doc:`hideText<globals/hideText>`         | Hide the text window                     |
    +-------------------------------------------+------------------------------------------+
    | :doc:`setTextAlign<globals/setTextAlign>` | Set text alignment                       |
    +-------------------------------------------+------------------------------------------+

**Visuals**

.. table::
    :widths: 1 100

    +---------------------------------------------+-----------------------------+
    | Function                                    | Description                 |
    +=============================================+=============================+
    | :doc:`setBackground<globals/setBackground>` | Change the background image |
    +---------------------------------------------+-----------------------------+
    | :doc:`scene<globals/scene>`                 | Transition to a new scene   |
    +---------------------------------------------+-----------------------------+


**User input**

.. table::
    :widths: 1 100

    +-----------------------------------------------------+--------------------------------+
    | Function                                            | Description                    |
    +=====================================================+================================+
    | :doc:`disableSkip<globals/disableSkip>`             | Disable ``Ctrl`` functionality |
    |                                                     | and make blocking transtions   |
    |                                                     | unskippable                    |
    +-----------------------------------------------------+--------------------------------+
    | :doc:`enableSkip<globals/enableSkip>`               | Enable ``Ctrl`` functionality  |
    |                                                     | and make blocking transitions  |
    |                                                     | skippable                      |
    +-----------------------------------------------------+--------------------------------+
    | :doc:`disableMouseInput<globals/disableMouseInput>` | Disable elements that accept   |
    |                                                     | mouse input such as buttons    |
    +-----------------------------------------------------+--------------------------------+
    | :doc:`enableMouseInput<globals/enableMouseInput>`   | Enable elements that accept    |
    |                                                     | mouse input such as buttions   |
    +-----------------------------------------------------+--------------------------------+
    | :doc:`getMousePosition<globals/getMousePosition>`   | Get the position of the mouse  |
    +-----------------------------------------------------+--------------------------------+
    | :doc:`setCursor<globals/setCursor>`                 | Change the cursor icon         |
    +-----------------------------------------------------+--------------------------------+
    | :doc:`setOnRightClick<globals/setOnRightClick>`     | Specify a function to call     |
    |                                                     | when the player presses the    |
    |                                                     | right mouse button             |
    +-----------------------------------------------------+--------------------------------+


**Sound**

.. table::
    :widths: 1 100

    +-------------------------------------------+--------------------------------------------+
    | Function                                  | Description                                |
    +===========================================+============================================+
    | :doc:`playMusic<globals/playMusic>`       | Start playing background music             |
    +-------------------------------------------+--------------------------------------------+
    | :doc:`fadeInMusic<globals/fadeInMusic>`   | Start playing background music with a fade |
    +-------------------------------------------+--------------------------------------------+
    | :doc:`stopMusic<globals/stopMusic>`       | Stop playing background music              |
    +-------------------------------------------+--------------------------------------------+
    | :doc:`fadeOutMusic<globals/fadeOutMusic>` | Stop playing background music with a fade  |
    +-------------------------------------------+--------------------------------------------+
    | :doc:`playSound<globals/playSound>`       | Play a sound                               |
    +-------------------------------------------+--------------------------------------------+
    | :doc:`stopSound<globals/stopSound>`       | Stop a sound                               |
    +-------------------------------------------+--------------------------------------------+


**Game control**

.. table::
    :widths: 1 100

    +-------------------------------------------------+-------------------------------------------------------------------+
    | Function                                        | Description                                                       |
    +=================================================+===================================================================+
    | :doc:`yield<globals/yield>`                     | Pause Lua execution until the next frame                          |
    +-------------------------------------------------+-------------------------------------------------------------------+
    | :doc:`sleep<globals/sleep>`                     | Pause Lua execution for the specified time                        |
    +-------------------------------------------------+-------------------------------------------------------------------+
    | :doc:`getDeltaSeconds<globals/getDeltaSeconds>` | Get the number of seconds elapsed since the last execution of Lua |
    +-------------------------------------------------+-------------------------------------------------------------------+
    | :doc:`openScript<globals/openScript>`           | Transfer execution to the specified script                        |
    +-------------------------------------------------+-------------------------------------------------------------------+
    | :doc:`exitGame<globals/exitGame>`               | Close the game                                                    |
    +-------------------------------------------------+-------------------------------------------------------------------+
    | :doc:`saveScreenshot<globals/saveScreenshot>`   | Save a screenshot of the game to a file                           |
    +-------------------------------------------------+-------------------------------------------------------------------+


**Caching**

.. table::
    :widths: 1 100

    +---------------------------------------------+------------------------------+
    | Function                                    | Description                  |
    +=============================================+==============================+
    | :doc:`precacheImage<globals/precacheImage>` | Precache the specified image |
    +---------------------------------------------+------------------------------+



Classes
=======

.. toctree::
    :hidden:

    classes/character/top
    classes/question/top
    classes/sprite/top
    classes/button/top
    classes/text/top
    classes/rectangle/top
    classes/video/top
    classes/characterSprite/top
    classes/cursor/top
    classes/clickableMap/top

.. table::
    :widths: 1 100

    +-----------------------------------------------------+----------------------------------------------------+
    | Class                                               | Description                                        |
    +=====================================================+====================================================+
    | :doc:`Character<classes/character/top>`             | A character that can be used for dialogue          |
    +-----------------------------------------------------+----------------------------------------------------+
    | :doc:`Question<classes/question/top>`               | Used to present a choice to the player             |
    +-----------------------------------------------------+----------------------------------------------------+
    | :doc:`Sprite<classes/sprite/top>`                   | An image that can be drawn on the screen           |
    +-----------------------------------------------------+----------------------------------------------------+
    | :doc:`Button<classes/button/top>`                   | A button the user can click                        |
    +-----------------------------------------------------+----------------------------------------------------+
    | :doc:`Text<classes/text/top>`                       | Used to draw text on the screen                    |
    +-----------------------------------------------------+----------------------------------------------------+
    | :doc:`Rectangle<classes/rectangle/top>`             | Used to draw a filled rectangle on the screen      |
    +-----------------------------------------------------+----------------------------------------------------+
    | :doc:`Video<classes/video/top>`                     | A video player                                     |
    +-----------------------------------------------------+----------------------------------------------------+
    | :doc:`CharacterSprite<classes/characterSprite/top>` | An image that represents a character               |
    +-----------------------------------------------------+----------------------------------------------------+
    | :doc:`Cursor<classes/cursor/top>`                   | A mouse cursor icon                                |
    +-----------------------------------------------------+----------------------------------------------------+
    | :doc:`ClickableMap<classes/clickableMap/top>`       | Used to make certain areas of the screen clickable |
    +-----------------------------------------------------+----------------------------------------------------+



Enumerations
============

.. toctree::
    :hidden:

    enums/position
    enums/transition
    enums/interpolator

.. table::
    :widths: 1 100

    +-----------------------------------------+--------------------------------------------------------+
    | Enumeration                             | Description                                            |
    +=========================================+========================================================+
    | :doc:`Position<enums/position>`         | Used to align text and character sprites on the screen |
    +-----------------------------------------+--------------------------------------------------------+
    | :doc:`Transition<enums/transition>`     | Types of transitions                                   |
    +-----------------------------------------+--------------------------------------------------------+
    | :doc:`Interpolator<enums/interpolator>` | Interpolation functions                                |
    +-----------------------------------------+--------------------------------------------------------+
