#include "ImageDissolveShader.h"
#include "GPUTexture.h"

bool ImageDissolveShader::loadProgram()
{
	bool success = loadProgramFromFiles(u8"shaders/common.vert", u8"shaders/imageDissolve.frag");

	maskLocation = GPU_GetUniformLocation(getProgramID(), "maskImage");
	transitionStepLocation = GPU_GetUniformLocation(getProgramID(), "transitionStep");

	return success;
}

void ImageDissolveShader::setMaskImage(const ITexture* mask)
{
	GPUTexture* gpuMask = (GPUTexture*)mask;

	GPU_SetShaderImage(gpuMask->getInternalTexture(), maskLocation, 2);
}

void ImageDissolveShader::setTransitionStep(float transitionStep)
{
	GPU_SetUniformf(transitionStepLocation, transitionStep);
}
