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

	else if(y == 0.5)
		fFragColor = vec4(0,0,1,0.5);

	else 
		fFragColor = uFaceColor;


}

