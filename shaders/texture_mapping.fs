#version 410
out vec4 FragColor;

in vec2 TextureCoord;

uniform sampler2D texture1;

void main()
{
    FragColor = texture(texture1, TextureCoord);
}