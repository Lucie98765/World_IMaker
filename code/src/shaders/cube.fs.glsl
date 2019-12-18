#version 330 core

in vec3 vVertexPosition;
in vec3 vVertexNormal;

out vec3 fFragColor;

void main() {
    fFragColor = normalize(vVertexNormal);
}

