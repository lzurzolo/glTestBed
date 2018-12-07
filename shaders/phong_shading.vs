#version 410

layout (location = 0) in vec3 VertexPosition;
layout (location = 1) in vec3 VertexNormal;

out vec3 LightIntensity;

uniform vec4 LightPosition;
uniform vec3 Ld;
uniform vec3 La;
uniform vec3 Ls;
uniform float Shininess;

uniform vec3 Kd;
uniform vec3 Ka;
uniform vec3 Ks;

uniform mat4 ModelView;
uniform mat4 ModelViewProjection;
uniform mat3 Normal;
uniform mat4 Projection;

void main()
{  
    vec3 n = normalize(Normal * VertexNormal);
    vec4 camCoords = ModelView * vec4(VertexPosition, 1.0);

    vec3 ambient = La * Ka;

    vec3 s = normalize(vec3(LightPosition - camCoords));
    float sDotN = max(dot(s, n), 0.0);
    vec3 diffuse = Ld * Kd * sDotN;

    vec3 spec = vec3(0.0);
    if(sDotN > 0.0)
    {
        vec3 v = normalize(-camCoords.xyz);
        vec3 r = reflect(-s, n);
        spec = Ls * Ks * pow(max(dot(r,v), 0.0), Shininess);
    }

    LightIntensity = ambient + diffuse + spec;
    gl_Position = ModelViewProjection * vec4(VertexPosition, 1.0);
}