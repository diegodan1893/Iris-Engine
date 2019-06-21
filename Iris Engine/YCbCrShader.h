#pragma once

#include "GPUShaderProgram.h"

/// <summary>
/// A shader used to convert from
/// Y'CbCr to RGB
/// </summary>
/// <seealso cref="GPUShaderProgram" />
class YCbCrShader : public GPUShaderProgram
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
	/// <param name="chroma">The Y'CbCr chroma components as a texture.</param>
	void setParameters(const class ITexture* chroma);

private:
	int chromaLocation;
};