#pragma once

#include "ResourcesManager.h"

class Shader : public IResource
{
public:
	Shader();
	~Shader();

	bool SetVertex(std::filesystem::path const& filename);
	bool SetFragment(std::filesystem::path const& filename);
	bool Link();

	void Load(std::string name) {};
	void UnLoad() {};

	int GetProgram()
	{
		return shaderProgram;
	}

private:
	int vertexShader;
	int fragmentShader;
	int shaderProgram;
};