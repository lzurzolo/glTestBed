#version 410

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 LightIntensity;

uniform vec4 LightPosition;
uniform vec3 Kd;
uniform vec3 Ld;

uniform mat4 ModelView;
uniform mat4 ModelViewProjection;
uniform mat3 Normal;
uniform mat4 Projection;


void main()
{
    vec3 tnorm = normalize(Normal * VertexNormal);
    vec4 camCoords = ModelView * vec4(VertexPosition, 1.0);
    vec3 s = normalize(vec3(LightPosition - camCoords));

    LightIntensity = Ld * Kd * max(dot(s, tnorm), 0.0);

    gl_Position = ModelViewProjection * vec4(VertexPosition, 1.0);
}