// Iris Engine.cpp : Defines the entry point for the application.
//

#include "Iris Engine.h"
#include <SDL2_gpu/SDL_gpu.h>

using namespace std;

int main(int argc, char* args[])
{
	GPU_Init(800, 600, 0);

	cout << "Hello CMake." << endl;
	return 0;
}
