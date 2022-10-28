cmake_minimum_required (VERSION 3.12)

find_package(sol2 CONFIG REQUIRED)
find_package(lua CONFIG REQUIRED)
find_package(SDL2 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_library(SDL_GPU_LIBRARY SDL2_gpu_s)

add_executable (IrisEngine "Iris.cpp" "Game/Game.h" "Game/Game.cpp")

target_link_libraries(
	IrisEngine
	PRIVATE
	sol2
	lua
	SDL2::SDL2 SDL2::SDL2main
	OpenGL32
	${SDL_GPU_LIBRARY}
)

set_property(TARGET IrisEngine PROPERTY CXX_STANDARD 20)
