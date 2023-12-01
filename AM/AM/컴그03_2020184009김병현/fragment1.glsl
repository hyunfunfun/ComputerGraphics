#version 330 core

//in vec3 out_Color;
//out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 lightColor; 
uniform vec3 objectColor;
uniform int lightSwitch;

void main()
{	
	/*�ں��Ʈ ���ϴ� ����*/
	float ambientLight = 0.5; //���� ��������.
	vec3 ambient = ambientLight * lightColor; //�ֺ� ���� ��, �ں��Ʈ���� �ֺ� ���� ���� 1.0f���� ����ȴ�. (���Ӽ��п��� ��� �� �̷��� ���� ������ ������� �ʴ´ٰ� �߾���)

	vec3 normalVector = normalize (Normal); //�븻���� ����ȭ�Ѵ�. �븻������ ���� ����ȭ �Ǿ� ��. �׷��� ������ ����� ����� �� ����.
	vec3 lightDir = normalize(lightPos - FragPos); //ǥ��� ������ ��ġ�� ������ ������ �����Ѵ�. ���� ���� ��������.
	float diffuseLight = max(dot (normalVector, lightDir), 0.0);//��ֺ��Ϳ� ���� ������ ����(������ ���� �� ������ �ּҰ� 0.0���� ����)
	vec3 diffuse = diffuseLight * lightColor; //��� �ݻ� ���� �� = ��� �ݻ� �� * ���� ���� ��	
	vec3 result = (ambient + diffuse) * objectColor;//���� ���� = (�ֺ� ���� * ��� �ݻ� ����) * ��ü ���� 
	if (lightSwitch == 1){
		 result = (ambient) * objectColor;
	}
	FragColor = vec4 (result, 1.0);
}
