#version 330 core

in vec2 ex_TexCoord;
out vec4 out_Color;

uniform sampler2D tex;

uniform float Time;

void main(void)
{
//    float factor = (sin(Time * 3.0) + 1.0) / 2.0;
    float factor = Time / 10;

    vec2 texCoord = vec2(ex_TexCoord.x + factor, ex_TexCoord.y);
    out_Color = texture(tex, texCoord);
}