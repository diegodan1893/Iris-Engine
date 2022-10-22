# Iris Engine

Iris Engine is a visual novel engine that will help you tell interactive stories.

Its scripting language, [Lua](https://www.lua.org/), is really easy to learn, so
you will be able to express your ideas even if you don't know anything about
programming. Here is an example of a conversation between two characters:

```lua
-- First, give a name to your characters
h = Character.new("Haru")
s = Character.new("Sakura")

-- And let them speak
h "Hi there!"
s "This is all you need to do to display dialogue on the screen."
h "Easy, right?"
```

Please note that Iris Engine is still in development and some important features
have not been implemented yet. Using it for production is not recommended.

# Getting Started

* [Latest stable release](https://github.com/diegodan1893/Iris-Engine/releases/latest)
* [Tutorial: Your first game with Iris Engine](https://iris-engine.readthedocs.io/en/latest/getting_started/first_game.html)
* [Full documentation](http://iris-engine.readthedocs.io/)
* [Example games](https://github.com/diegodan1893/Iris-Engine-Examples)

# System requirements

* TBD

# Building from source

> This section is intended for programmers who want to extend Iris Engine or
> contribute to its development. If you just want to use Iris Engine to create a
> game, refer to the [getting started section](#getting-started).

Iris Engine uses [CMake](https://cmake.org/) to coordinate the build process and
[vcpkg](https://vcpkg.io/en/index.html) to automatically install its
dependencies.

## Building on Windows

1. [Install vcpkg](https://vcpkg.io/en/getting-started.html).
2. Create a new environment variable called `VCPKG_ROOT` and set it to the installation folder of vcpkg.
3. Clone the Iris Engine repo and open it with Visual Studio 2022 or newer.
4. Build the project (Build > Build All). The dependencies will be downloaded and built automatically.
	* If you get errors, try opening any of the `CMakeLists.txt` files and saving it without making any changes to regenerate the CMake output.
