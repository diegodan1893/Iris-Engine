#include "TestShader.h"

bool TestShader::loadProgram()
{
	bool success = loadProgramFromFiles(u8"shaders/common.vert", u8"shaders/color.frag");

	return success;
}
