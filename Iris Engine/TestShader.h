#pragma once

#include "GPUShaderProgram.h"

/// <summary>
/// A test shader used to check that
/// everything is working correctly.
/// </summary>
/// <seealso cref="GPUShaderProgram" />
class TestShader : public GPUShaderProgram
{
public:
	/// <summary>
	/// Loads the program.
	/// </summary>
	/// <returns><c>true</c> if the program was loaded successfully; otherwise <c>false</c>.</returns>
	bool loadProgram() override;
};