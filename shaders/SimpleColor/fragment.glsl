#version 330 core

in vec4 ex_Color;
out vec4 out_Color;

void main(void)
{
    if (any(lessThan(ex_Color, vec4(0.02))))
        out_Color = ex_Color;
    else 
        out_Color = vec4(0,0,0,0);
}