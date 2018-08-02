#pragma once

#include "GPUShaderProgram.h"

/// <summary>
/// A shader used to create image dissolve
/// transitions.
/// </summary>
/// <seealso cref="GPUShaderProgram" />
class ImageDissolveShader : public GPUShaderProgram
{
public:
	/// <summary>
	/// Loads the program.
	/// </summary>
	/// <returns><c>true</c> if the program was loaded successfully; otherwise <c>false</c>.</returns>
	bool loadProgram() override;
	
	/// <summary>
	/// Sets the image to use as the mask
	/// for the transition.
	/// The shader must be binded first,
	/// otherwise the result is undefined behavior
	/// </summary>
	/// <param name="mask">The texture to use as the mask.</param>
	void setMaskImage(const class ITexture* mask);
	
	/// <summary>
	/// Sets at what point whe are in the transition.
	/// The shader must be binded first,
	/// otherwise the result is undefined behavior
	/// </summary>
	/// <param name="transitionStep">At what point we are in the transition, 0 is the start and 1 the end.</param>
	void setTransitionStep(float transitionStep);

private:
	int maskLocation;
	int transitionStepLocation;
};