#version 330 core

in vec4 in_Position;
in vec4 in_Color;
in vec2 in_TexCoord;
in vec3 in_Normal;

out vec4 ex_Color;
out vec2 ex_TexCoord;
out vec3 ex_Normal;

uniform mat4 ModelMatrix;

uniform SharedMatrices {
    mat4 ViewMatrix;
    mat4 ProjectionMatrix;
};

void main(void)
{
    vec4 ModelColor = vec4(0.9, 0.5, 0.5, 1.0);

    gl_Position = (ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position).xyww;

//    mat3 normalMatrix = transpose(inverse(mat3(ViewMatrix * ModelMatrix)));
    mat3 normalMatrix = transpose(inverse(mat3(ModelMatrix)));
    ex_Normal = normalMatrix * in_Normal;
    ex_Color = ModelColor;
    ex_TexCoord = in_TexCoord;
}