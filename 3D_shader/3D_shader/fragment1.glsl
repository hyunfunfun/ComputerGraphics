#version 330 core

out vec4 FragColor;

uniform vec3 objectColor;
uniform vec3 lightColor;

void main(void){
	
	float ambientLight=0.5;
	vec3 ambient = ambientLight * lightColor;

	vec3 result=ambient*objectColor;

	FragColor=vec4(result,1.0);
}