#version 330 core

in vec4 ex_Color;
out vec4 out_Color;

void main(void)
{
    if (any(lessThan(ex_Color, vec4(0.01))))
        out_Color = vec4(0.7,0.7,0.7,1.0);
    else 
        out_Color = vec4(0,0,0,0);
}