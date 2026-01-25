#include "Texture.h"
#include "stb_image.h"

Texture::Texture(std::string filename, GLuint mode)
{
	Load("Assets/Textures/" + filename);
	SetMode(mode);
	Bind();
}

Texture::~Texture()
{
	delete [] data;
}

void Texture::Load(std::string filename)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	LoadTextureFlag(mode);
	SetAnisotropy(anisotropy);

	stbi_set_flip_vertically_on_load(true); // Flip texture so it can be properly applied
	data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 4); // load and generate the texture
	path = filename;

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		DEBUG_LOG("This file doesn't exist (" + filename + ")");
	}

	maxAnisotropy = 20.f;
}

void Texture::LoadTextureFlag(GLuint param)
{
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, param);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, param);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Texture::SetAnisotropy(float value)
{
	float maxAnisotropy = GetMaxAnisotropy();

	anisotropy = value > maxAnisotropy ? maxAnisotropy : value;
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, anisotropy);
}

void Texture::SetMode(GLuint value)
{
	mode = value;
}

GLuint Texture::GetMode() const
{
	return GLuint(mode);
}

std::string Texture::GetPath() const
{
	return path;
}

float Texture::GetAnisotropy() const
{
	return anisotropy;
}

float Texture::GetMaxAnisotropy() const
{
	return maxAnisotropy;
}

void Texture::UnLoad()
{
	delete this;
}

void Texture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, texture);
	glActiveTexture(GL_TEXTURE0);


	anisotropy = 1.f;
	LoadTextureFlag(mode);
	SetAnisotropy(anisotropy);
}

void Texture::Unbind()
{
	stbi_image_free(data);
	glDeleteTextures(1, &texture);
}

Cubemap::Cubemap(Texture t1, Texture t2, Texture t3, Texture t4, Texture t5, Texture t6)
{
	texture_face.push_back(t1);
	texture_face.push_back(t2);
	texture_face.push_back(t3);
	texture_face.push_back(t4);
	texture_face.push_back(t5);
	texture_face.push_back(t6);

	Load(texture_face);
}

void Cubemap::Load(std::vector<Texture> textures)
{
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	LoadCubemapFlags();

	for (unsigned int i = 0; i < texture_face.size(); i++)
	{
		data = stbi_load(texture_face[i].GetPath().c_str(), &width, &height, &nrChannels, 4); // load and generate the texture

		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			DEBUG_LOG("This file doesn't exist (" + texture_face[i].GetPath() + ")");
		}
	}
}

void Cubemap::LoadCubemapFlags()
{
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}