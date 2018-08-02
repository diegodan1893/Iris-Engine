#include "DissolveShader.h"
#include "GPUTexture.h"

bool DissolveShader::loadProgram()
{
	bool success = loadProgramFromFiles(u8"shaders/common.vert", u8"shaders/dissolve.frag");

	previousTextureLocation = GPU_GetUniformLocation(getProgramID(), "previous");
	transitionStepLocation = GPU_GetUniformLocation(getProgramID(), "transitionStep");

	return success;
}

void DissolveShader::setParameters(const ITexture* previousTexture, float transitionStep)
{
	GPUTexture* gpuPreviousTexture = (GPUTexture*)previousTexture;

	GPU_SetShaderImage(gpuPreviousTexture->getInternalTexture(), previousTextureLocation, 1);
	GPU_SetUniformf(transitionStepLocation, transitionStep);
}
