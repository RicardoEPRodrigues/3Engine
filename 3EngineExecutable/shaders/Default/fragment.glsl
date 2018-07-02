#version 330 core

in vec2 ex_TexCoord;
out vec4 out_Color;

uniform sampler2D tex;

void main(void)
{
    out_Color = texture(tex, ex_TexCoord) * vec4(0.9, 0.5, 0.5, 1.0);
}