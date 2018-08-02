#pragma once

#include "IShaderProgram.h"
#include <SDL_gpu.h>
#include <cinttypes>
#include <string>

/// <summary>
/// A shader program that uses the SDL_gpu library.
/// </summary>
/// <seealso cref="IShaderProgram" />
class GPUShaderProgram : public IShaderProgram
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="GPUShaderProgram"/> class.
	/// </summary>
	GPUShaderProgram();
	virtual ~GPUShaderProgram();
	
	/// <summary>
	/// Activates the shader so that the
	/// following render calls use it.
	/// </summary>
	void bind() override;
	
	/// <summary>
	/// Deactivates the shader program.
	/// </summary>
	void unbind() override;

protected:	
	/// <summary>
	/// Loads and compiles a shader program.
	/// </summary>
	/// <param name="vertexShaderFile">The vertex shader source file.</param>
	/// <param name="fragmentShaderFile">The fragment shader source file.</param>
	/// <returns><c>true</c> if the program was loaded successfully; otherwise <c>false</c>.</returns>
	bool loadProgramFromFiles(
		const std::string& vertexShaderFile,
		const std::string& fragmentShaderFile
	);
	
	/// <summary>
	/// Gets the program identifier.
	/// </summary>
	/// <returns>The ID of this shader program.</returns>
	uint32_t getProgramID();

private:
	uint32_t programObject;
	GPU_ShaderBlock programBlock;
};