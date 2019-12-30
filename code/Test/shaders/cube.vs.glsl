#version 330 core

layout(location = 0) in vec3 aVertexPosition;
layout(location = 1) in vec3 aVertexNormal;

uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

out vec3 vVertexPosition;
out vec3 vVertexAbsolutePosition;
out vec3 vVertexNormal;


void main(){
    //Passage en coordonnées homogènes :
    vec4 vertexPosition = vec4(aVertexPosition, 1);

    //Calcul des valeurs de sortie :
    vVertexPosition = vec3(uMVMatrix * vertexPosition);

    //Calcul de la position projetée :
    gl_Position = uMVPMatrix * vertexPosition;

    vVertexAbsolutePosition = aVertexPosition;

    //Passage de la normale
    vec4 vertexNormal = vec4(aVertexNormal, 0); //0 car vecteur
    vVertexNormal = vec3(uNormalMatrix * vertexNormal );

}