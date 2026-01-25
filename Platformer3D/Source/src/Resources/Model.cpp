#include "Model.h"

Model::Model(std::string nameObjFile)
{
    Load("Assets/Meshes/" + nameObjFile);
}

Model::~Model()
{
    vertices.clear();
    indexes.clear();
}

void Model::UnLoad()
{
    delete this;
}

void Model::Load(std::string nameObjFile)
{
    std::ifstream file;

    file.open(nameObjFile);
    if (!file.is_open())
    {
        DEBUG_LOG("This file doesn't exist (" + nameObjFile + ")");
        file.close();
        return;
    }

    std::string str;
    std::string line;

    std::vector<Vector3D> posObj;
    Vector3D v;

    std::vector<Vector2D> textCoordObj;
    Vector2D vt;

    std::vector<Vector3D> normalObj;
    Vector3D vn;

    std::map<std::string, size_t> tupleIndex;

    Vertex vertex;

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        iss >> str;

        if (str == "v")
        {
            for (int indexInVector3D = 0; indexInVector3D < 3; ++indexInVector3D)
            {
                iss >> str;
                v[indexInVector3D] = std::stof(str);
            }

            posObj.push_back(v);
        }
        else if (str == "vt")
        {
            for (int indexInVector2D = 0; indexInVector2D < 2; ++indexInVector2D)
            {
                iss >> str;
                vt[indexInVector2D] = std::stof(str);
            }

            textCoordObj.push_back(vt);
        }
        else if (str == "vn")
        {
            for (int indexInVector3D = 0; indexInVector3D < 3; ++indexInVector3D)
            {
                iss >> str;
                vn[indexInVector3D] = std::stof(str);
            }

            normalObj.push_back(vn);
        }
        else if (str == "f")
        {
            std::vector<int> indexVertexPolygon;
            while (iss >> str)
            {
                auto it = tupleIndex.find(str);
                if (it == tupleIndex.end())
                {
                    tupleIndex[str] = vertices.size();

                    std::string vertexInOrder;
                    int i = 0;
                    for (i; i < str.length(); ++i)
                    {
                        if (str[i] == '/')
                            break;
                        else
                        {
                            vertexInOrder += str[i];
                        }
                    }
                    Vector3D currentVertexPosition = posObj[std::stoull(vertexInOrder) - 1];
                    vertex.position.x = currentVertexPosition.x; vertex.position.y = currentVertexPosition.y; vertex.position.z = currentVertexPosition.z;

                    ++i;
                    std::string textCoordsInOrder;
                    for (; i < str.length(); ++i)
                    {
                        if (str[i] == '/')
                            break;
                        else
                            textCoordsInOrder += str[i];
                    }
                    Vector2D currentVertexUV = textCoordObj[std::stoull(textCoordsInOrder) - 1];
                    vertex.textureUV.x = currentVertexUV.x; vertex.textureUV.y = currentVertexUV.y;


                    ++i;
                    std::string normalInOrder;
                    for (; i < str.length(); ++i)
                    {
                        if (str[i] == '/')
                            break;
                        else
                            normalInOrder += str[i];
                    }
                    Vector3D currentVertexNormal = normalObj[std::stoull(normalInOrder) - 1];
                    vertex.normal.x = currentVertexNormal.x; vertex.normal.y = currentVertexNormal.y; vertex.normal.z = currentVertexNormal.z;


                    indexVertexPolygon.push_back(tupleIndex[str]);
                    vertices.push_back(vertex);
                }
                else
                {
                    indexVertexPolygon.push_back(it->second);
                }
            }

            size_t nbVertexInPoly = indexVertexPolygon.size();

            indexes.push_back(indexVertexPolygon[0]);
            indexes.push_back(indexVertexPolygon[1]);
            indexes.push_back(indexVertexPolygon[2]);

            if (nbVertexInPoly > 3)
            {
                for (size_t indexInPoly = 3; indexInPoly < nbVertexInPoly; ++indexInPoly)
                {
                    indexes.push_back(indexVertexPolygon[0]);
                    indexes.push_back(indexVertexPolygon[indexInPoly - 1]);
                    indexes.push_back(indexVertexPolygon[indexInPoly]);
                }
            }
        }
    }

    normalObj.clear();
    textCoordObj.clear();
    posObj.clear();

    file.close();
    return;
}

Model::Buffer::Buffer()
{
    glGenBuffers(1, &buffer);
}

Model::Buffer::~Buffer()
{
    glDeleteBuffers(1, &buffer);
}

void Model::Buffer::Bind(GLenum type)
{
    glBindBuffer(type, buffer);
}

void Model::Buffer::SetData(GLenum type, GLsizeiptr size, const GLvoid* data, GLenum usage)
{
    glBufferData(type, size, data, usage);
}

Model::VertexAttributes::VertexAttributes()
{
    glGenVertexArrays(1, &vertex);
}

Model::VertexAttributes::~VertexAttributes()
{
    glDeleteVertexArrays(1, &vertex);
}

void Model::VertexAttributes::Bind()
{
    glBindVertexArray(vertex);
}

void Model::VertexAttributes::SetAttributes(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer)
{
    glVertexAttribPointer(index, size, type, normalized, stride, pointer);
    glEnableVertexAttribArray(index);
}
