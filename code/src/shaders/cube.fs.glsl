#version 330 core

in vec3 vVertexPosition;
in vec3 vVertexAbsolutePosition;
in vec3 vVertexNormal;

out vec4 fFragColor;

uniform vec4 uFaceColor;
uniform vec4 uEdgeColor;
uniform bool uEdgeMode;

//Directionnal light uniform variable
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;
uniform bool uIsLightDir; //tells if a directionnal light is placed or not

//Point light uniform variable
uniform vec3 uLightPos_vs; //position of the point light
uniform bool uIsPointLight; //tells if a point light is placed or not


//Directionnal light Blinn Phong
vec4 blinnPhong_dir(){
	vec3 result;
	vec3 wi = normalize(uLightDir_vs);
	vec3 w0 = normalize(-vVertexPosition);
	vec3 halfV = (w0 + wi)/2;
	vec3 r1 = uKs * pow(dot(halfV, vVertexNormal), uShininess);
	vec3 r2  = uLightDir_vs*(uKd*dot(wi, vVertexNormal));
	result = uLightIntensity*(r1 + r2);

	if(0 != uFaceColor.a && uIsLightDir){
		return vec4(result, 1);
	} else {
		return vec4(0, 0, 0, 0);
	}

}


//Point light Blinn Phong
vec4 blinnPhong_point(vec3 lightPosition){
	vec3 result;
	vec3 wi = normalize(lightPosition - vVertexPosition);
	vec3 w0 = normalize(-vVertexPosition);
	vec3 halfV = (w0 + wi)/2;
	vec3 r1 = uKs * pow(dot(halfV, vVertexNormal), uShininess);
	vec3 r2  = lightPosition*(uKd*dot(wi, vVertexNormal));
	float distance = distance (vVertexPosition, lightPosition);
	result = (uLightIntensity*2/(distance*distance))*(r1 + r2);
	
	if(0 != uFaceColor.a && uIsPointLight){
		return vec4(result, 1);
	} else {
		return vec4(0, 0, 0, 0);
	}


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
		fFragColor = uEdgeColor + blinnPhong_dir() + blinnPhong_point(uLightPos_vs);
	} else if(((-0.5-e <= x && x <= -0.5+e) || (0.5-e <= x && x <= 0.5+e))
			&&
		((-0.5-e <= z && z <= -0.5+e) || (0.5-e <= z && z <= 0.5+e)))
	{
		fFragColor = uEdgeColor + blinnPhong_dir() + blinnPhong_point(uLightPos_vs);

	} else if(((-0.5-e <= z && z <= -0.5+e) || (0.5-e <= z && z <= 0.5+e))
			&&
		((-0.5-e <= y && y <= -0.5+e) || (0.5-e <= y && y <= 0.5+e)))
	{
		fFragColor = uEdgeColor + blinnPhong_dir() + blinnPhong_point(uLightPos_vs);

	} else {
		fFragColor = uFaceColor + blinnPhong_dir() + blinnPhong_point(uLightPos_vs);
	}


	if(uEdgeMode){
		fFragColor.a = 0;
	}

}


