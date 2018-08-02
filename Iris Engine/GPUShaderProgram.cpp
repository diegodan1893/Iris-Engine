#include "GPUShaderProgram.h"
#include "Locator.h"

GPUShaderProgram::GPUShaderProgram()
	:programObject(0)
{
}

GPUShaderProgram::~GPUShaderProgram()
{
	GPU_FreeShaderProgram(programObject);
}

void GPUShaderProgram::bind()
{
	GPU_ActivateShaderProgram(programObject, &programBlock);
}

void GPUShaderProgram::unbind()
{
	GPU_DeactivateShaderProgram();
}

bool GPUShaderProgram::loadProgramFromFiles(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
{
	bool success = true;
	uint32_t vertex, fragment;

	// Load vertex shader
	vertex = GPU_LoadShader(GPU_VERTEX_SHADER, vertexShaderFile.c_str());
	
	if (!vertex)
	{
		Locator::getLogger()->log(
			LogCategory::RENDER,
			LogPriority::ERROR,
			u8"Failed to load vertex shader:\n" + std::string(GPU_GetShaderMessage())
		);

		success = false;
	}
	else
	{
		// Load fragment shader
		fragment = GPU_LoadShader(GPU_FRAGMENT_SHADER, fragmentShaderFile.c_str());

		if (!fragment)
		{
			Locator::getLogger()->log(
				LogCategory::RENDER,
				LogPriority::ERROR,
				u8"Failed to load fragment shader:\n" + std::string(GPU_GetShaderMessage())
			);

			success = false;
			GPU_FreeShader(vertex);
		}
		else
		{
			// Link program
			programObject = GPU_LinkShaders(vertex, fragment);

			if (!programObject)
			{
				Locator::getLogger()->log(
					LogCategory::RENDER,
					LogPriority::ERROR,
					u8"Failed to link shader program:\n" + std::string(GPU_GetShaderMessage())
				);

				success = false;
				GPU_FreeShader(vertex);
				GPU_FreeShader(fragment);
			}
			else
			{
				// Create program block
				programBlock = GPU_LoadShaderBlock(
					programObject,
					"gpu_Vertex",
					"gpu_TexCoord",
					"gpu_Color",
					"gpu_ModelViewProjectionMatrix"
				);
			}
		}
	}

	return success;
}

uint32_t GPUShaderProgram::getProgramID()
{
	return programObject;
}
