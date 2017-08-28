#version 330 core

layout(location = 0) in vec3 vertexPos;

uniform mat4 MVP;

out vec3 color;

void main() {
    color = vec3(vertexPos.x + 1, vertexPos.y + 1, vertexPos.z + 1);
    gl_Position = MVP * vec4(vertexPos, 1.0);

}
