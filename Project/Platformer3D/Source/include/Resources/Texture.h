#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "ResourcesManager.h"

#define STB_IMAGE_IMPLEMENTATION

class Texture : public IResource
{
public:
	Texture() = default;
	Texture(std::string filename, GLuint mode = GL_REPEAT);
	~Texture();

	void SetAnisotropy(float value);
	void SetMode(GLuint value);

	float GetAnisotropy() const;
	float GetMaxAnisotropy() const;

	GLuint GetMode() const;
	std::string GetPath() const;

	void Bind();
	void Unbind();

private:
	void UnLoad() override;
	void Load(std::string filename) override;
	void LoadTextureFlag(GLuint param = GL_REPEAT);

	unsigned char* data;
	int width, height, nrChannels;

	std::string path;
	GLuint mode;
	unsigned int texture;
	float anisotropy;
	float maxAnisotropy;
};

class Cubemap : private Texture
{
public:
	Cubemap() = default;
	Cubemap(Texture t1, Texture t2, Texture t3, Texture t4, Texture t5, Texture t6);
	~Cubemap() = default;

	void Load(std::vector<Texture> textures);
	void LoadCubemapFlags();
	int GetTexture()
	{
		return texture;
	}

private:
	std::vector<Texture> texture_face;

	unsigned int texture;
	unsigned char* data;
	int width, height, nrChannels;
};