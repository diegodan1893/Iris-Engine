#pragma once

#include "GPUShaderProgram.h"

/// <summary>
/// A shader used to create dissolve
/// transitions for CharacterObjects.
/// </summary>
/// <seealso cref="GPUShaderProgram" />
class DissolveShader : public GPUShaderProgram
{
public:	
	/// <summary>
	/// Loads the program.
	/// </summary>
	/// <returns><c>true</c> if the program was loaded successfully; otherwise <c>false</c>.</returns>
	bool loadProgram() override;
	
	/// <summary>
	/// Sets the parameters of the shader.
	/// The shader must be binded first,
	/// otherwise the result is undefined behavior
	/// </summary>
	/// <param name="previousTexture">The texture of the image we are transitioning from.</param>
	/// <param name="transitionStep">At what point we are in the transition, 0 is the start and 1 the end.</param>
	void setParameters(const class ITexture* previousTexture, float transitionStep);

private:
	int previousTextureLocation;
	int transitionStepLocation;
};