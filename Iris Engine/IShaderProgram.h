#pragma once

/// <summary>
/// A shader program.
/// </summary>
class IShaderProgram
{
public:
	virtual ~IShaderProgram() {}
	
	/// <summary>
	/// Loads the program.
	/// </summary>
	/// <returns><c>true</c> if the program was loaded successfully; otherwise <c>false</c>.</returns>
	virtual bool loadProgram() = 0;
	
	/// <summary>
	/// Activates the shader so that the
	/// following render calls use it.
	/// </summary>
	virtual void bind() = 0;
	
	/// <summary>
	/// Deactivates the shader program.
	/// </summary>
	virtual void unbind() = 0;
};