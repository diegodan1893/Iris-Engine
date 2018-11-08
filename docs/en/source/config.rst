The config file
===============

The config file, named ``config.lua`` and located in the same folder as the Iris
Engine executable, is a Lua script that defines some variables that control the
behavior of the game.

In this page you can find detailed information about all the settings you can
customize in the config file.

.. tip::
	You don't need to create a config file from scratch. Download a
	:doc:`template<getting_started/templates>` and edit the included config file
	to suit your needs.



Game
----

This section contains the description of your game.

``name``
	The name of your game. It will be displayed as the title of the window.

``iconFile``
	Path to the image to use as the icon of your game. It will be displayed in the
	Windows taskbar and it will be used as the icon of the window of your game.
	This image can be in any :doc:`supported format<formats>`.

``startScript``
	Path to the script to run when the game starts.

	This path must be relative to the *scripts* path specified in the paths_ section.



Screen
------

This section defines the properties of the window of your game.

``fullscreen``
	Whether to launch the game in fullscreen mode.

	The player can toggle fullscreen mode by pressing ``Alt+Enter``.

``resolution``
	The native resolution of your game.

	The game will be rendered at this resolution and then scaled to the actual size of
	the window using letterboxing when necessary.



Text window
-----------

This section defines the properties of the box where the text of dialogue and
narration appears.

``position``
	The position of the :term:`text window`.

``size``
	The size in pixels of the :term:`text window`.

``margin``
	The margin allows you to leave some space between the area where the text will be
	written and the borders of the text window. This space is specified in pixels.

``background``
	Path to the image to use as the background of the :term:`text window`. This image
	will be stretched to fill the text window.

	This path must be relative to the *gui* path specified in the paths_ section.

``backgroundAlpha``
	The opacity of the background image of the :term:`text window` defined as a number
	in the range [0, 255] where 0 is completely transparent and 255 the opacity of the
	original image.

``font``
	Path to the font file to use to render the text of your game.

``fontSize``
	The point size (based on 72 DPI) of the font to use to render the dialogue and
	narration text of your game.

``fontColor``
	The color in *rgb* of the narration and dialogue text of your game.

``shadowDistance``
	Distance in pixels of the drop shadow of the text of your game. If set to 0, no
	shadow will be drawn.

``shadowColor``
	The color in *rgba* of the drop shadow of the text of your game.

``spacing``
	Line spacing in pixels. This will be added to the recommended line spacing of
	your font, which it's usually a few more pixels than necessary for lines to not
	overlap. Negative numbers bring lines together.

``wordWrapping``
	If enabled, the text of the :term:`text window` will be split breaking lines
	between words rather than within words, when possible.

``formatJapaneseText``
	If enabled, pages that start with '「', '『' or '（' will be indented as is
	common in Japanese visual novels.

	.. figure:: media/formatJapanese_true.png
		:align: center
		
		formatJapaneseText enabled

	.. figure:: media/formatJapanese_false.png
		:align: center

		formatJapaneseText disabled

``characterDelay``
	Controls the typewriter effect of the :term:`text window`. The time in seconds
	it takes for each character to appear.

``namePosition``
	The position within the :term:`text window` of the name of the character that is
	speaking.

``nameFontSize``
	The point size (based on 72 DPI) of the name of the character that is speaking.

``nameFontColor``
	The color in *rgb* of the name of the character that is speaking.

``nameShadowDistance``
	Distance in pixels of the drop shadow of the name of the character that is
	speaking. If set to 0, no sadow will be drawn.

``nameShadowColor``
	The color in *rgba* of the drop shadow of the name of the character that is
	speaking.

``indicatorImage``
	Path to the image to use to tell the player that they can click to dismiss the
	text currently displayed in the :term:`text window`.

	The arrow in the bottom right corner of this image is an example of an indicator
	image:

	.. figure:: media/formatJapanese_true.png
		:align: center

	The indicator image will be treated as a sprite sheet.

	This path must be relative to the *gui* path specified in the paths_ section.

``indicatorPosition``
	The position of the indicator image within the :term:`text window`.

``showIndicatorAfterLastCharacter``
	If true, ``indicatorPosition`` will be ignored and the indicator image will be
	placed after the last character of text.

	.. figure:: media/indicator_lastCharacter.png
		:align: center
		
		showIndicatorAfterLastCharacter set to true

``indicatorSpriteSheet``
	The properties of the sprite sheet of the indicator image.

``showTransition``
	Properties of the transition used to make the :term:`text window` visible.

``hideTransition``
	Properties of the transition used to make the :term:`text window` invisible.



Choices
-------

This section defines the properties of the menus used to present choices to the
player.

``position``
	Position of the area where the options will appear. The buttons will be
	vertically and horizontally centered in this area.

``size``
	Size in pixels of the area where the options will appear. The buttons will be
	vertically and horizontally centered in this area.

``background``
	The background image used to create the buttons. Read
	:doc:`language/api/classes/button/constructor` for more details.

``useVerticalLayout``
	Wether the layout of the background image used to create the buttons is vertical.
	Read :doc:`language/api/classes/button/constructor` for more details.

``separation``
	Distance in pixels from the top left corner of one button to the top left corner
	of the next.

``showTransition``
	Properties of the transition used to show the options to the player.

``hideTransition``
	Properties of the transition used to hide the options.



Paths
-----

This section defines the folders where the most common asset types are located, so
that you don't have to write the full path when using these assets in your scripts.
They can all point to the same folder if you want to.

``scripts``
	Path to the folder where scripts are located.

``sprites``
	Path to the folder where images of sprites are located.

``characters``
	Path to the folder where images of character sprites are located.

``backgrounds``
	Path to the folder where background images are located.

``transitions``
	Path to the folder where control images of imageDissolve transitions are
	located.

``gui``
	Path to the folder where GUI images are located.

``music``
	Path to the folder where the soundtrack of your game is located.

``sounds``
	Path to the folder where the sounds of your game are located.

``separator``
	String used as a separator when constructing the filenames of expression images.



Sounds
------

This section defines some GUI sounds.

``buttonHoverSound``
	Path to the sound to play when the mouse enters a button.

	This path must be relative to the *sounds* path specified in the paths_ section.

``buttonClickSound``
	Path to the sound to play when the player clicks a button.

	This path must be relative to the *sounds* path specified in the paths_ section.



Z-indexes
---------

While visual novels are 2D games, when two objects overlap we need to know which one
should be drawn on top of the other. For this reason, all objects that can be drawn
on the screen have a z-index. You can think of z-indexes as the layers of a drawing
program.

An object with greater z-index is always in front of an object with a lower z-index.

This section defines the default z-index of some objects of the game.

``sceneTransitionEffects``
	Some transition effects draw an image in front of all of the objects of the
	scene. This is the z-index of those effects. Should be the highest.

``textWindow``
	The z-index of the :term:`text window`.

``choices``
	The z-index of the menus used to present choices to the player.

``characters``
	The default z-index of character sprites.

``backgrounds``
	The z-index of the background.



Cache
-----

Images, sounds and other assets need to be loaded into memory before they can be
used in the game. However, loading takes time and can cause stutter and framerate
drops during gameplay. For this reason, once an asset has been loaded, it remains in
memory as long as possible so that the next time it is needed we don't have to load
it again. The part of the memory where these assets reside is called the *cache*.

This section defines the properties of the cache and controls the way Iris Engine
loads assets into memory.

``maxSizeInMiB``
	The maximum size of the cache in MiB. Keep in mind that this only takes into
	account the size of the assets themselves, so the actual memory requirements of
	your game will be higher.

``allowPrecaching``
	Iris Engine loads assets the first time they are needed. This means that the
	images of sprites, for example, are loaded the first time the sprite is
	displayed on the screen. This can cause stutter during gameplay.

	However, if this option is enabled, the loading will take place when the object
	is defined, which is usually at the beginning of the script. This way, the
	player will be less likely to notice the stutter, especially if the loading
	happens just before a scene transition.

``finishLoadingSceneTransitions``
	As backgrounds don't need to be defined, they can't be precached even if
	``allowPrecaching`` is enabled. This may result in the game skipping the first
	frames of scene transitions.

	If this option is enabled, the start of scene transitions will be delayed until
	the background image has been loaded, making it impossible for the player to
	notice the stutter.

	This option only has an effect on
	:doc:`the scene function<language/api/globals/scene>`.