#pragma once

#include "GPUShaderProgram.h"

/// <summary>
/// A shader used to apply color grading
/// to an image using a color LUT table.
/// </summary>
/// <seealso cref="GPUShaderProgram" />
class ColorGradingShader : public GPUShaderProgram
{
public:	
	/// <summary>
	/// Loads the program.
	/// </summary>
	/// <returns><c>true</c> if the program was loaded successfully; otherwise <c>false</c>.</returns>
	bool loadProgram() override;
	
	/// <summary>
	/// Sets the parameters of the shader for simple color grading.
	/// The shader must be binded first,
	/// otherwise the result is undefined behavior.
	/// </summary>
	/// <param name="colorLUT">The texture to use as color LUT.</param>
	void setParameters(const class ITexture* colorLUT);
	
	/// <summary>
	/// Sets the parameters of the shader for a LUT transition from the original color.
	/// The shader must be binded first,
	/// otherwise the result is undefined behavior.
	/// </summary>
	/// <param name="colorLUT">The texture to use as color LUT.</param>
	/// <param name="transitionStep">The transition step.</param>
	void setParameters(const class ITexture* colorLUT, float transitionStep);
	
	/// <summary>
	/// Sets the parameters of the shader for a LUT transition blending two LUTs.
	/// The shader must be binded first,
	/// otherwise the result is undefined behavior.
	/// </summary>
	/// <param name="colorLUTfrom">The color lu tfrom.</param>
	/// <param name="colorLUTto">The color lu tto.</param>
	/// <param name="transitionStep">The transition step.</param>
	void setParameters(
		const class ITexture* colorLUTfrom,
		const class ITexture* colorLUTto,
		float transitionStep
	);

private:
	int colorLUTfromLocation;
	int colorLUTtoLocation;
	int transitionStepLocation;
	int blendLUTsLocation;
};