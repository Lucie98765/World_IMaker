#version 330 core

in vec3 vVertexPosition;
in vec3 vVertexAbsolutePosition;
in vec3 vVertexNormal;

out vec4 fFragColor;

uniform vec4 uFaceColor;
uniform vec4 uEdgeColor;
uniform int uEdgeMode;

//Directionnal light uniform variables
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;


vec4 blinnPhong(){
	vec3 result;
	vec3 wi = normalize(uLightDir_vs);
	vec3 w0 = normalize(-vVertexPosition);
	vec3 halfV = (w0 + wi)/2;
	vec3 r1 = uKs * pow(dot(halfV, vVertexNormal), uShininess);
	vec3 r2  = uLightDir_vs*(uKd*dot(wi, vVertexNormal));
	result = uLightIntensity*(r1 + r2);
	if(0 == uFaceColor.a){
		return vec4(result, 0);
	} else {
		return vec4(result, 1);
	}
	return vec4(result, 1);

}

void main() {

	float x = vVertexAbsolutePosition.x;
	float y = vVertexAbsolutePosition.y;
	float z = vVertexAbsolutePosition.z;

	float e = 0.01;

	if(((-0.5-e <= x && x <= -0.5+e) || (0.5-e <= x && x <= 0.5+e))
		&&
		((-0.5-e <= y && y <= -0.5+e) || (0.5-e <= y && y <= 0.5+e)))
	{
		fFragColor = uEdgeColor + blinnPhong();
	} else if(((-0.5-e <= x && x <= -0.5+e) || (0.5-e <= x && x <= 0.5+e))
			&&
		((-0.5-e <= z && z <= -0.5+e) || (0.5-e <= z && z <= 0.5+e)))
	{
		fFragColor = uEdgeColor + blinnPhong();
	} else if(((-0.5-e <= z && z <= -0.5+e) || (0.5-e <= z && z <= 0.5+e))
			&&
		((-0.5-e <= y && y <= -0.5+e) || (0.5-e <= y && y <= 0.5+e)))
	{
		fFragColor = uEdgeColor + blinnPhong();
	}

	/*else if(z == -0.5)
		fFragColor = vec4(0,0,1,0.5);*/

	else
		fFragColor = uFaceColor + blinnPhong();

	if(0 == uEdgeMode)
		fFragColor.a = 0;

}

