#version 330 core

in vec3 vVertexPosition;

out vec4 fFragColor;

uniform vec4 uFaceColor;
uniform vec4 uEdgeColor;

void main() {

	float x = vVertexPosition.x;
	float y = vVertexPosition.y;
	float z = vVertexPosition.z;
	

	/*if(
	((y == -0.5f || y == 0.5f) && (z == -0.5f || z == 0.5f))
		||
	((x == -0.5f || x == 0.5f) && (z == -0.5f || z == 0.5f))
		||
	((x == -0.5f || x == 0.5f) && (y == -0.5f || y == 0.5f))
	)
		fFragColor = uEdgeColor;
	else*/
		fFragColor = uFaceColor;

}

