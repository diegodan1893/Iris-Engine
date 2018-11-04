The Button class
================

This class is used to create buttons the player can interact with using the mouse.

Buttons are actually :doc:`sprites<../sprite/top>`, which means you can use methods
like :doc:`move<../sprite/move>` to animate them, but they offer additional
functionality to handle mouse input.

In order to create a button you will need an image like this:

.. image:: /media/exit_btn.png

This image includes the four possible states of a button:

* Up: when the player is not interacting with the button
* Hover: when the mouse is over the button
* Down: when the button is being pressed
* Disabled: when the player is not allowed to interact with the button
  
In the previous example we've included the text of the button in the image itself,
but this is not necessary, as this class allows you to add a string of text on top
of the image.

You can control the actions that will be performed when the player interacts with
the button using the properties_ defined below.


Properties
^^^^^^^^^^

.. toctree::
    :hidden:

    enabled
    onMouseEnter
    onMouseExit
    onClick

.. table::
    :widths: 1 1 1 100

    +------------+-----------------------------------+---------------+-------------------------------------------------------------+
    | Type       | Name                              | Default value | Description                                                 |
    +============+===================================+===============+=============================================================+
    | *bool*     | :doc:`enabled<enabled>`           | *true*        | Sets whether or not the player can interact with the button |
    +------------+-----------------------------------+---------------+-------------------------------------------------------------+
    | *function* | :doc:`onMouseEnter<onMouseEnter>` | *nil*         | Sets the function to call when the mouse enters the button  |
    +------------+-----------------------------------+---------------+-------------------------------------------------------------+
    | *function* | :doc:`onMouseExit<onMouseExit>`   | *nil*         | Sets the function to call when the mouse leaves the button  |
    +------------+-----------------------------------+---------------+-------------------------------------------------------------+
    | *function* | :doc:`onClick<onClick>`           | *nil*         | Sets the function to call when the player clicks the button |
    +------------+-----------------------------------+---------------+-------------------------------------------------------------+

The Button class inherits all of the properties of
:doc:`the Sprite class <../sprite/top>`.


Member functions
^^^^^^^^^^^^^^^^

.. toctree::
    :hidden:

    constructor

.. table::
    :widths: 1 100

    +-----------------------------------+------------------------+
    | Method                            | Description            |
    +===================================+========================+
    | :doc:`(constructor)<constructor>` | Create a Button object |
    +-----------------------------------+------------------------+

The Button class inherits all of the methods of
:doc:`the Sprite class <../sprite/top>`.