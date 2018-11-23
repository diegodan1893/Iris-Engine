#include "ColorGradingShader.h"
#include "GPUTexture.h"

bool ColorGradingShader::loadProgram()
{
	bool success = loadProgramFromFiles(u8"shaders/common.vert", u8"shaders/colorGrading.frag");

	colorLUTfromLocation = GPU_GetUniformLocation(getProgramID(), "colorLUTfrom");
	colorLUTtoLocation = GPU_GetUniformLocation(getProgramID(), "colorLUTto");
	transitionStepLocation = GPU_GetUniformLocation(getProgramID(), "transitionStep");
	blendLUTsLocation = GPU_GetUniformLocation(getProgramID(), "blendLUTs");

	return success;
}

void ColorGradingShader::setParameters(const ITexture* colorLUT)
{
	GPUTexture* gpuColorLUT = (GPUTexture*)colorLUT;

	GPU_SetShaderImage(gpuColorLUT->getInternalTexture(), colorLUTfromLocation, 1);
	GPU_SetUniformf(transitionStepLocation, 0.0f);
}

void ColorGradingShader::setParameters(const ITexture* colorLUT, float transitionStep)
{
	GPUTexture* gpuColorLUT = (GPUTexture*)colorLUT;

	GPU_SetShaderImage(gpuColorLUT->getInternalTexture(), colorLUTfromLocation, 1);
	GPU_SetUniformf(transitionStepLocation, transitionStep);
	GPU_SetUniformi(blendLUTsLocation, false);
}

void ColorGradingShader::setParameters(const ITexture * colorLUTfrom, const ITexture * colorLUTto, float transitionStep)
{
	GPUTexture* gpuColorLUTfrom = (GPUTexture*)colorLUTfrom;
	GPUTexture* gpuColorLUTto = (GPUTexture*)colorLUTto;

	GPU_SetShaderImage(gpuColorLUTfrom->getInternalTexture(), colorLUTfromLocation, 1);
	GPU_SetShaderImage(gpuColorLUTto->getInternalTexture(), colorLUTtoLocation, 2);
	GPU_SetUniformf(transitionStepLocation, transitionStep);
	GPU_SetUniformi(blendLUTsLocation, true);
}
