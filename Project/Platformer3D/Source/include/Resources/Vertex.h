#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "MathPerso.h"

struct Vertex
{
	Vector3D position;
	Vector2D textureUV;
	Vector3D normal;

	//GLfloat color[];
};

bool operator==(const Vertex& v1, const Vertex& v2);

//Vertex g_Triangles[] = {{-0.5f,-0.5f},
//						{0.5f,-0.5f},	
//						{0.f,0.5f} };
//
//uint16_t g_Indices[] = { 0,1,2 };

// VBO 1/ save pos,color normal des sommets
// EBO 2/ indice des sommets
// VAO 3/ met tt en commun

//glgen -> gl delete		VAO gl.....VertexArrays		VBO / EBO  gl..Buffers