#version 330 core

out vec4 out_Color;

uniform vec4 ModelColor;

void main(void)
{
    out_Color = ModelColor;
}