Button constructor
==================

:Syntax:
	| Button.new(*string* image, *number* zindex, *bool* verticalLayout = false)
	| Button.new(*string* image, *number* zindex, *string* text, *bool* verticalLayout = false)

Constructs a Button object using the provided background image.


Parameters
^^^^^^^^^^

+----------+----------------+----------------------------------------------------------------------------------+
| Type     | Name           | Description                                                                      |
+==========+================+==================================================================================+
| *string* | image          | The background image of the button; see remarks_ for details                     |
+----------+----------------+----------------------------------------------------------------------------------+
| *number* | zindex         | The z-index of this sprite                                                       |
+----------+----------------+----------------------------------------------------------------------------------+
| *string* | text           | The text of the button                                                           |
+----------+----------------+----------------------------------------------------------------------------------+
| *bool*   | verticalLayout | Whether the layout of the background image is vertical; see remarks_ for details |
+----------+----------------+----------------------------------------------------------------------------------+


Remarks
^^^^^^^

The path of the *image* parameter must be relative to the *gui* path
specified in the :doc:`config<../../../../config>` file.

The provided image should include the background for the four possible states of
a button in the following order:

* Up: when the player is not interacting with the button
* Hover: when the mouse is over the button
* Down: when the button is being pressed
* Disabled: when the player is not allowed to interact with the button

If ``verticalLayout`` is ``false``, the engine expect them to be aligned horizontally,
like in this example:

.. image:: /media/exit_btn.png

If ``verticalLayout`` is ``true``, they should be aligned vertically, like this:

.. image:: /media/question_btn.png


Examples
^^^^^^^^

.. code-block:: lua

    -- Create a button with horizontal layout and no text
    button1 = Button.new("exit_btn.png", 1)

    -- Create a button with vertical layout and no text
    button2 = Button.new("choices_BG.png", 1, true)

    -- Create a button with horizontal layout and the text "Start"
    button3 = Button.new("start_btn.png", 1, "Start")

    -- Create a button with vertical layout and the text "Go to school"
    button4 = Button.new("choices_BG.png", 1, "Go to school", true)


See also
^^^^^^^^

* :doc:`../sprite/top`