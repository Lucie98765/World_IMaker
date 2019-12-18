#version 330 core

in vec3 vVertexPosition;
in vec3 vVertexAbsolutePosition;

out vec4 fFragColor;

uniform vec4 uFaceColor;
uniform vec4 uEdgeColor;

void main() {

	float x = vVertexAbsolutePosition.x;
	float y = vVertexAbsolutePosition.y;
	float z = vVertexAbsolutePosition.z;
	

	/*if((y == -0.5f || y == 0.5f) && (z == -0.5f || z == 0.5f))
		fFragColor = uEdgeColor;

	else if((x == -0.5f || x == 0.5f) && (z == -0.5f || z == 0.5f))
		fFragColor = uEdgeColor;

	else if((x == -0.5f || x == 0.5f) && (y == -0.5f || y == 0.5f))
		fFragColor = uEdgeColor;

	else
		fFragColor = uFaceColor;*/

	float e = 0.01;

	if(
		((-0.5-e <= x && x <= -0.5+e) || (0.5-e <= x && x <= 0.5+e))
			&&
		((-0.5-e <= y && y <= -0.5+e) || (0.5-e <= y && y <= 0.5+e))
	)
		fFragColor = uEdgeColor;
	else if(
		((-0.5-e <= x && x <= -0.5+e) || (0.5-e <= x && x <= 0.5+e))
			&&
		((-0.5-e <= z && z <= -0.5+e) || (0.5-e <= z && z <= 0.5+e))
	)
		fFragColor = uEdgeColor;
	else if(
		((-0.5-e <= z && z <= -0.5+e) || (0.5-e <= z && z <= 0.5+e))
			&&
		((-0.5-e <= y && y <= -0.5+e) || (0.5-e <= y && y <= 0.5+e))
	)
		fFragColor = uEdgeColor;

	else 
		fFragColor = uFaceColor;


}

