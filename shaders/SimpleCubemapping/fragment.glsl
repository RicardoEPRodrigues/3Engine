#version 330 core

in vec4 ex_Color;
in vec2 ex_TexCoord;
in vec3 ex_Normal;
out vec4 out_Color;

uniform samplerCube cube_tex;

void main(void)
{
    out_Color = texture(cube_tex, ex_Normal);
}