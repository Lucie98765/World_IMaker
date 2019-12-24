#version 330 core

in vec3 vVertexPosition;
in vec3 vVertexAbsolutePosition;

out vec4 fFragColor;

uniform vec4 uFaceColor;
uniform vec4 uEdgeColor;
uniform int uEdgeMode;

//Directionnal light
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;


vec4 blinnPhong(){
	vec3 wi = normalize(uLightDir_vs);
	vec3 halfVector = normalize(-vVertexPosition);
	vec3 p1 = uKd*(dot(wi, normalize(vVertexAbsolutePosition)));
	vec3 p2 = uKs*pow((dot(halfVector, normalize(vVertexAbsolutePosition))), uShininess);
	vec3 color = uLightIntensity*(p1+p2);
	return vec4(color, 1);
}

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
		fFragColor = blinnPhong() * uEdgeColor;
	else if(
		((-0.5-e <= x && x <= -0.5+e) || (0.5-e <= x && x <= 0.5+e))
			&&
		((-0.5-e <= z && z <= -0.5+e) || (0.5-e <= z && z <= 0.5+e))
	)
		fFragColor = blinnPhong() * uEdgeColor;
	else if(
		((-0.5-e <= z && z <= -0.5+e) || (0.5-e <= z && z <= 0.5+e))
			&&
		((-0.5-e <= y && y <= -0.5+e) || (0.5-e <= y && y <= 0.5+e))
	)
		fFragColor = blinnPhong() * uEdgeColor;

	/*else if(z == -0.5)
		fFragColor = vec4(0,0,1,0.5);*/

	else
		fFragColor = blinnPhong() * uFaceColor;
	if(0 == uEdgeMode)
		fFragColor.a = 0;

}

