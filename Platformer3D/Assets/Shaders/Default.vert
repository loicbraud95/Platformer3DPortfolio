#version 330 core

in layout (location = 0) vec3 pos;
in layout (location = 1) vec2 uv;
in layout (location = 2) vec3 normal;
in layout (location = 3) vec3 color;

uniform mat4x4 MVP;
uniform mat4 modelMatrix;

out VertexOut
{
    vec3 fragPos;
    vec3 normalPos;
    vec2 uvPos;
    vec4 fragColor;
} vertexOut;

// ligne - colonne 

void main()
{
    vec4 vec4Normal = vec4(normal, 1.f);
    vec4 posVec4 = vec4(pos, 1.f);
    gl_Position = (MVP * posVec4);

    vertexOut.fragPos = vec3(modelMatrix * posVec4);
    vertexOut.normalPos = mat3(transpose(inverse(modelMatrix))) * normal;
    vertexOut.uvPos = uv;
    vertexOut.fragColor = vec4(color, 1.f);
}