#version 330 core

layout(location = 0) in vec3 aVertexPosition;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 vVertexPosition;


void main(){
    //Passage en coordonnées homogènes :
    vec4 vertexPosition = vec4(aVertexPosition, 1);

    //Calcul des valeurs de sortie :
    vVertexPosition = vec3(uMVMatrix * vertexPosition);

    //Calcul de la position projetée :
    gl_Position = uMVPMatrix * vertexPosition;

}