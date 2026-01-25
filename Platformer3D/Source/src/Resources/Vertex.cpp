#include "Vertex.h"

bool operator==(const Vertex& v1, const Vertex& v2)
{
	if (v1.textureUV == v2.textureUV && v1.position == v2.position && v1.normal == v2.normal)
		return true;
	return false;
}