#version 330 core

in vec3 vVertexPosition;
in vec3 vVertexAbsolutePosition;
in vec3 vVertexNormal;

out vec4 fFragColor;

uniform vec4 uFaceColor;
uniform vec4 uEdgeColor;
uniform int uEdgeMode;

//Directionnal light uniform variable
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;
uniform bool u_is_dir_light; //tells if a directionnal light is placed or not

//Point light uniform variable
uniform vec3 uLightPos_vs; //position of the point light
uniform bool u_is_point_light; //tells if a point light is placed or not


//Directionnal light Blinn Phong
vec4 blinnPhong(){
	vec3 result;
	vec3 wi = normalize(uLightDir_vs);
	vec3 w0 = normalize(-vVertexPosition);
	vec3 halfV = (w0 + wi)/2;
	vec3 r1 = uKs * pow(dot(halfV, vVertexNormal), uShininess);
	vec3 r2  = uLightDir_vs*(uKd*dot(wi, vVertexNormal));
	result = uLightIntensity*(r1 + r2);

	if(0 != uFaceColor.a && u_is_dir_light){
		return vec4(result, 1);
	} else {
		return vec4(0, 0, 0, 0);
	}

}


//Point light Blinn Phong
vec4 blinnPhong(vec3 light_pos){
	vec3 result;
	vec3 wi = normalize(light_pos - vVertexPosition);
	vec3 w0 = normalize(-vVertexPosition);
	vec3 halfV = (w0 + wi)/2;
	vec3 r1 = uKs * pow(dot(halfV, vVertexNormal), uShininess);
	vec3 r2  = light_pos*(uKd*dot(wi, vVertexNormal));
	float distance = distance (vVertexPosition, light_pos);
	result = (uLightIntensity/(distance*distance))*(r1 + r2);
	
	if(0 != uFaceColor.a && u_is_point_light){
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
		fFragColor = uEdgeColor + blinnPhong() + blinnPhong(uLightPos_vs);
	} else if(((-0.5-e <= x && x <= -0.5+e) || (0.5-e <= x && x <= 0.5+e))
			&&
		((-0.5-e <= z && z <= -0.5+e) || (0.5-e <= z && z <= 0.5+e)))
	{
		fFragColor = uEdgeColor + blinnPhong() + blinnPhong(uLightPos_vs);

	} else if(((-0.5-e <= z && z <= -0.5+e) || (0.5-e <= z && z <= 0.5+e))
			&&
		((-0.5-e <= y && y <= -0.5+e) || (0.5-e <= y && y <= 0.5+e)))
	{
		fFragColor = uEdgeColor + blinnPhong() + blinnPhong(uLightPos_vs);

	} else {
		fFragColor = uFaceColor + blinnPhong() + blinnPhong(uLightPos_vs);
	}


	if(0 == uEdgeMode){
		fFragColor.a = 0;
	}

}


