#include "YCbCrShader.h"
#include "GPUTexture.h"

bool YCbCrShader::loadProgram()
{
	bool success = loadProgramFromFiles(u8"shaders/common.vert", u8"shaders/YCbCr.frag");

	chromaLocation = GPU_GetUniformLocation(getProgramID(), "chromaTex");

	return success;
}

void YCbCrShader::setParameters(const ITexture * chroma)
{
	GPUTexture* gpuChroma = (GPUTexture*)chroma;

	GPU_SetShaderImage(gpuChroma->getInternalTexture(), chromaLocation, 1);
}
