#version 410

layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec3 VertexNormal;
layout(location = 2) in vec2 UV;

uniform mat4 ModelViewProjection;
out vec2 TextureCoord;

void main()
{
    gl_Position = ModelViewProjection * vec4(VertexPosition, 1.0);
    TextureCoord = UV;
}