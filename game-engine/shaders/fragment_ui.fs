#version 330 core
out vec4 FragColor;
uniform vec4 spriteColor;

void main()
{
    FragColor = vec4(spriteColor);
}
