#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Vertex.h"
#include "ResourcesManager.h"
#include "Log.h"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

class Model : public IResource
{
public:
	Model(std::string nameObjFile);
	~Model();

	std::vector<Vertex> vertices;
	std::vector<uint32_t> indexes;
	
	void UnLoad() override;

private:
	class Buffer
	{
	public:
		Buffer();
		~Buffer();

		void Bind(GLenum type);
		void SetData(GLenum type, GLsizeiptr size, const GLvoid* data, GLenum usage);

		GLuint buffer;
	};

	class VertexAttributes
	{
	public:
		VertexAttributes();
		~VertexAttributes();

		void Bind();
		void SetAttributes(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer);

		GLuint vertex;
	};

	void Load(std::string nameObjFile) override;

public:
	Buffer vbo;
	Buffer ebo;
	VertexAttributes vertexAttributes;
};