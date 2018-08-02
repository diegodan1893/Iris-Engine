-- Config file

game = {
	-- The name of the game. It will be displayed in the title of the window.
	name = "Juego de prueba",

	-- Path to the icon of the window. The file can be in any supported format.
	iconFile = "assets/images/icon.png",

	-- First script
	startScript = "_start.lua"
}


screen = {
	-- Whether to start the game in fullscreen mode the first time it is launched
	fullscreen = false, -- @todo move to default user settings

	-- Native resolution of the game
	resolution = {x = 1280, y = 720}
}


-- The box where the text of the dialogue appears
textWindow = {
	-- Position and size of the window in pixels
	position = {x = 100, y = 100},
	size = {w = 1280-200, h = 720-200},

	-- Marign of the text area inside the window
	margin = {
		top = 50,
		right = 50,
		bottom = 50,
		left = 50,
	},

	-- Background image
	background = "textWindow_BG4.png",
	backgroundAlpha = 190, -- @todo move to default user settings

	-- Font options
	font = "assets/fonts/AdobeHebrew-Regular.otf",
	fontSize = 30,
	fontColor = {r = 255, g = 255, b = 255},

	-- If 0 no shadow will be drawn
	shadowDistance = 2,
	shadowColor = {r = 0, g = 0, b = 0, a = 100},

	-- Line spacing in pixels. This will be added to the recommended spacing of your
	-- font, which it's usually a few more pixels than necessary for lines to not
	-- overlap. Negative numbers bring lines together.
	spacing = 0,

	-- Break lines betwen words.
	wordWrapping = true,

	-- Pages starting with '「', '『' or '（' will be indented
	-- Lines ending with '。' or '、' will be allowed to exceed the width limit
	formatJapaneseText = true,

	-- Character delay for typewriter effect in seconds
	characterDelay = 0.02, -- @todo move to default user settings

	-- Options for characters' names
	namePosition = {x = 171, y = 11},
	nameFontSize = 24,
	nameFontColor = {r = 255, g = 248, b = 189},
	nameShadowDistance = 2,
	nameShadowColor = {r = 0, g = 0, b = 0, a = 100},

	-- Next line indicator
	indicatorImage = "textReady.png",
	indicatorPosition = {x = 1090, y = 150},

	-- If true, indicatorPosition will be ignored and the indicator will be
	-- placed after the last character of text.
	showIndicatorAfterLastCharacter = true,

	indicatorSpriteSheet = {
		-- Leave at 1, 1, 1, 0 respectively for no animation
		frameCount = 14,
		columns = 7,
		rows = 2,
		fps = 30
	},

	-- Transitions
	showTransition = {time = 0.3},
	hideTransition = {time = 0.3}
}


-- The buttons that allow players to choose their own adventure
choices = {
	-- Position and size of the area where the buttons will be centered
	position = {x = 0, y = 0},
	size = {w = 1280, h = 519},

	-- Button background
	background = "choices_BG.png",
	useVerticalLayout = true,

	-- Separation between buttons based on their origins in both axes
	separation = {x = 20, y = 60},

	-- Transitions
	showTransition = {timePerButton = 0.5, timeBetweenButtons = 0.05},
	hideTransition = {time = 0.3}
}


paths = {
	-- The folder where scripts are located
	scripts = "assets/scripts/",

	-- The folder where sprites are located
	sprites = "assets/images/sprites/",

	-- The folder where characters and expressions are located
	characters = "assets/images/characters/",

	-- The folder where backgrounds are located
	backgrounds = "assets/images/backgrounds/",

	-- The folder where transition images are located
	transitions = "assets/images/transitions/",

	-- The folder where gui images are located
	gui = "assets/images/gui/",

	-- The folder where BGM files are located
	music = "assets/music/",

	-- The folder where sound effects are located
	sounds = "assets/sounds/",

	-- String used as a separator when constructing filenames
	separator = " "
}


sounds = {
	-- All paths are relative to the sounds path specified in the paths section
	
	-- Buttons
	buttonHoverSound = "hover.ogg",
	buttonClickSound = "clic.ogg",
}


zindexes = {
	-- Zindex for scene transition effects, should be the highest.
	sceneTransitionEffects = 101,

	-- Zindex for the text window
	textWindow = 100,

	-- Zindex for choice buttons
	choices = 99,

	-- Default zindex for all characters
	characters = 50,

	-- Zindex for the background
	backgrounds = 0
}


-- Memory management
cache = {
	-- Maximum size of the cache in MiB
	maxSizeInMiB = 512,


	-- If enabled, assets will be loaded when objects are defined in the script.
	-- If disabled, they will be loaded the first time they are needed.
	-- 
	-- Precaching will increase load time of scripts but it can reduce FPS drops
	-- during gameplay as long as objects don't exceed the maximun size of the cache.
	-- Check the documentation for a more detailed explanation on caching.
	allowPrecaching = true,

	-- Delay scene transitions to allow backgrounds to finish loading before
	-- starting the animation.
	-- When enabled, the game will preload backgrounds in scene transitions and
	-- wait one frame before starting the animation. This way, framerate drops
	-- caused by loading will be unnoticed by the user.
	finishLoadingSceneTransitions = true
}