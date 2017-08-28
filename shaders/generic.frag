#version 330 core

in  vec3 color;
out vec3 frag;

void main() {
    frag = normalize(color);
}
