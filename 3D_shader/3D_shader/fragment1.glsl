#version 330 core
in vec4 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 objectColor; //--- ���� ���α׷����� ������ ��ü�� ����
uniform vec3 lightColor; //--- ���� ���α׷����� ������ ���� ����

void main ()
{
	float ambientLight = 0.3; //--- �ֺ� ���� ���: 0.0 �� ambientLight �� 1.0
	vec3 ambient=ambientLight*lightColor;

	vec3 normalVector = normalize(Normal);
	vec3 lightDir=normalize(lightPos-FragPos);
	float diffuseLight=max(dot(normalVector,lightDir),0.0);
	float diffuse = diffuseLight*lightColor;

	vec3 result = (ambient+diffuse) * objectColor; //--- ��ü�� ���� �ֺ������� ���Ͽ� ���� ��ü ���� ����

	FragColor = vec4 (result, 1.0);
}
