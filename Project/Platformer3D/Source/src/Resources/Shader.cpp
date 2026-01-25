#include "Shader.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>

Shader::Shader()
{
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	shaderProgram = glCreateProgram();
}

Shader::~Shader()
{
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glDeleteProgram(shaderProgram);
}

bool Shader::SetVertex(std::filesystem::path const& filename)
{
	try
	{
		std::ifstream in(filename);
		std::string contents((std::istreambuf_iterator<char>(in)),
		std::istreambuf_iterator<char>());

		const char* fileContent = contents.c_str();

		glShaderSource(vertexShader, 1, &fileContent, NULL);
		glCompileShader(vertexShader);

		int success;
		char log[512];
		glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(vertexShader, sizeof(log), NULL, log);
			std::string l = log;
			DEBUG_LOG("ERROR COMPILING VERTEX SHADER "+ l + "\n");
			return false;
		}
		else
			return true;
	}
	catch (const std::exception&)
	{
		DEBUG_LOG("Vertex shader could not load properly...\nAborting...");
		return false;
	}
}

bool Shader::SetFragment(std::filesystem::path const& filename)
{
	try
	{
		std::ifstream in(filename);
		std::string contents((std::istreambuf_iterator<char>(in)),
			std::istreambuf_iterator<char>());

		const char* fileContent = contents.c_str();

		glShaderSource(fragmentShader, 1, &fileContent, NULL);
		glCompileShader(fragmentShader);

		int success;
		char log[512];
		glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(fragmentShader, sizeof(log), NULL, log);
			std::string l = log;
			DEBUG_LOG("ERROR COMPILING VERTEX SHADER" + l +"\n");
			return false;
		}
		else
			return true;
	}
	catch (const std::exception&)
	{
		DEBUG_LOG("Vertex shader could not load properly...\nAborting...");
		return false;
	}
}

bool Shader::Link()
{
	try
	{
		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		int success;
		char log[512];

		glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

		if (!success)
		{
			glGetProgramInfoLog(shaderProgram, sizeof(log), NULL, log);
			std::string l = log;
			DEBUG_LOG("ERROR LINKING SHADER "+l+"\n");
			return false;
		}
		else
			return true;

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	catch (const std::exception&)
	{
		DEBUG_LOG("Shader could not be linked to program...\nAborting...");
		return false;
	}
}