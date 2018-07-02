#version 330 core

in vec4 in_Position;
in vec4 in_Color;
in vec2 in_TexCoord;
in vec3 in_Normal;
out vec2 ex_TexCoord;
out vec3 ex_Normal;

uniform mat4 ModelMatrix;

uniform SharedMatrices {
    mat4 ViewMatrix;
    mat4 ProjectionMatrix;
};

void main(void)
{
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;

//    mat3 normalMatrix = transpose(inverse(mat3(ViewMatrix) * mat3(ModelMatrix)));
//    ex_Normal = normalMatrix * in_Normal;

    ex_TexCoord = in_TexCoord;
}