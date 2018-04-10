#version 330 core

in vec4 in_Position;
in vec4 in_Color;
in vec2 in_TexCoord;
in vec3 in_Normal;

out vec4 ex_Color;
out vec2 ex_TexCoord;
out vec3 ex_Normal;
out vec3 ex_Eye;

uniform mat4 ModelMatrix;

uniform SharedMatrices {
    mat4 ViewMatrix;
    mat4 ProjectionMatrix;
};

void main(void)
{
    vec4 pos = ViewMatrix * ModelMatrix * in_Position;

    mat3 normalMatrix = transpose(inverse(mat3(ViewMatrix * ModelMatrix)));
//    mat3 normalMatrix = transpose(inverse(mat3(ModelMatrix)));

    ex_Normal = normalMatrix * in_Normal;
    ex_Color = in_Color;
    ex_TexCoord = in_TexCoord;
    ex_Eye = vec3(-pos);

    gl_Position = ProjectionMatrix * pos;
}