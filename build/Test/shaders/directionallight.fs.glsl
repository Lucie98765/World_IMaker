#version 330 core

in vec3 vVertexPosition;
in vec3 vVertexNormal;
in vec2 vVertexTextCoord;

uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;
uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

out vec3 fFragColor;

vec3 blinnPhong(){
	vec3 result;
	vec3 wi = normalize(uLightDir_vs);
	vec3 w0 = normalize(-vVertexPosition);
	vec3 halfvec = (w0 + wi)/2;
	vec3 r1 = uKs * pow(dot(halfvec, vVertexNormal), uShininess);
	vec3 r2  = uLightDir_vs*(uKd*dot(wi, vVertexNormal));
	result = r1 + r2;

	return result;
}

void main(){
	fFragColor = blinnPhong() * normalize(vVertexNormal);
	//fFragColor = texture(uTexture, vVertexTextCoord).xyz; //Il faut les coordonnées de la texture -> vec2D
}