#version 330 core

in vec4 in_Position;
in vec4 in_Color;
out vec4 ex_Color;

uniform mat4 ModelMatrix;
uniform vec4 ModelColor = vec4(0.5, 0.5, 0.5, 1.0);

uniform SharedMatrices {
    mat4 ViewMatrix;
    mat4 ProjectionMatrix;
};

void main(void)
{
    gl_Position = ProjectionMatrix * ViewMatrix * ModelMatrix * in_Position;

    float mixer = (ModelMatrix * in_Position).z;
    if (mixer > 1) {
        mixer = 1;
    } else {
        if (mixer < 0.3) {
            mixer = 0.3;
        }
    }
    ex_Color = vec4(ModelColor.x * mixer, ModelColor.y * mixer, ModelColor.z * mixer, ModelColor.w);
}