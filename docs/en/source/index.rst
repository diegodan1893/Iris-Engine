Welcome to Iris Engine's documentation!
=======================================

Iris Engine is a visual novel engine that will help you tell interactive stories.

It's scripting language, `Lua <https://www.lua.org/>`_, is really easy to learn,
so you will be able to express your ideas even if you don't know anything about
programming. Here is an example of a conversation between two characters:

.. code-block:: lua

	-- First, give a name to your characters
	h = Character.new("Haru")
	s = Character.new("Sakura")

	-- And let them speak
	h "Hi there!"
	s "This is all you need to do to display dialogue on the screen."
	h "Easy, right?"



Getting Started
---------------

:doc:`Your first game with Iris Engine<getting_started/first_game>`
	A step-by-step tutorial that will guide you through the creation of a
	simple game in Iris Engine from start to finish. You should start here.

:doc:`Examples and templates<getting_started/templates>`
	Use these as a base for your game so that you can start creating right away.

Working with visuals
	Learn how Iris Engine handles backgrounds, sprites and character sprites.

:doc:`API reference<language/api/top>`
	Here you will find detailed information about all the functions and classes
	available to you.

The config file
	Detailed information about all the settings you can change to make your game
	work the way you want.



.. toctree::
	:maxdepth: 2
	:caption: Contents:

	getting_started/top
	visuals
	language/top
	config
	formats
	glossary



Indices and tables
==================

* :ref:`genindex`
* :ref:`search`