#version 330 core

uniform vec3 viewPos;

in VertexOut
{
    vec3 fragPos;
    vec3 normalPos;
    vec2 uvPos;
    vec4 fragColor;
} vertexIn;

uniform sampler2D text; // texture sampler
uniform samplerCube cubemap; // cubemap texture sampler

struct DirectionalLight
{
	vec4 lightDirection;

	vec4 lightAmbientColor;
	vec4 lightDiffuseColor;
	vec4 lightSpecularColor;

	int enable;
	int filling1;
	int filling2;
	int filling3;

};

struct PointLight
{
	vec4 lightPosition;

	vec4 lightAmbientColor;
	vec4 lightDiffuseColor;
	vec4 lightSpecularColor;

	float constant;
	float linear;
	float quadratic;
	int enable;
};

struct SpotLight
{
	vec4 lightPosition;
	vec4 lightDirection;

	vec4 lightAmbientColor;
	vec4 lightDiffuseColor;
	vec4 lightSpecularColor;


	float cutOff;
	float outerCutOff;
	int enable;
	int filling3;
};

layout (std140) uniform Lights
{
	DirectionalLight directionalLights[4];
	PointLight pointsLights[4];
	SpotLight spotsLights[4];
	
	uint ubo;
	float filling1;
	float filling2;
	float filling3;

};

out vec4 FragColor;

void main()
{
	vec4 textColor = texture(text, vertexIn.uvPos);

	vec3 result = vec3(0,0,0);

	//ambient/diffuse/spec
	vec3 material[3];
	material[0] = vec3(0.05,0.05,0.06);
	material[1] = vec3(0.2,0.2,0.2);
	material[2] = vec3(0.3,0.3,0.3);

	float materialShininess = 0.3f;
	
	for (int i = 0; i < 4; ++i)
	{
		if (directionalLights[i].enable == 1)
		{
			DirectionalLight dir = directionalLights[i];

			//ambient
			vec3 ambient = vec3(dir.lightAmbientColor) * material[0] * vec3(textColor);
	
			//diffuse
			vec3 norm = normalize(vertexIn.normalPos);
			vec3 lightDir = normalize(vec3(-dir.lightDirection));
			float diff = max(dot(norm,lightDir), 0.0f);
			vec3 diffuse = vec3(dir.lightDiffuseColor) * (diff * material[1]) * vec3(textColor);

			//specular
			vec3 viewDir = normalize(viewPos - vertexIn.fragPos);

			//blinn
			vec3 halfwayDir = normalize(lightDir + viewDir);
			float spec = pow(max(dot(vertexIn.normalPos, halfwayDir), 0.0f), materialShininess);
			vec3 specular = vec3(dir.lightSpecularColor) * (spec * material[2]);

			result += (ambient + diffuse + specular);
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		if (pointsLights[i].enable == 1)
		{
			PointLight ptl = pointsLights[i];

			//ambient
			vec3 ambient =  vec3(ptl.lightAmbientColor) * material[0] * vec3(textColor);
	
			//diffuse
			vec3 norm = normalize(vertexIn.normalPos);
			vec3 lightDir = normalize(vec3(ptl.lightPosition) - vertexIn.fragPos);
			float diff = max(dot(norm,lightDir), 0.0f);
			vec3 diffuse = vec3(ptl.lightDiffuseColor) * (diff * material[1]) * vec3(textColor);

			//specular
			vec3 viewDir = normalize(viewPos - vertexIn.fragPos);

			//blinn
			vec3 halfwayDir = normalize(lightDir + viewDir);
			float spec = pow(max(dot(vertexIn.normalPos, halfwayDir), 0.0f), materialShininess);
			vec3 specular = vec3(ptl.lightSpecularColor) * (spec * material[2]);

			//attenuation
			float dist = length(ptl.lightPosition.xyz - vertexIn.fragPos);
			float attenuation = 1.0f / (ptl.constant + ptl.linear * dist + ptl.quadratic * (dist*dist));

			result += (ambient + diffuse + specular) * attenuation;
		}
	}

	for (int i = 0; i < 4; ++i)
	{
		if (spotsLights[i].enable == 1)
		{
			SpotLight sp = spotsLights[i];

			vec3 lightDir = normalize(vec3(sp.lightPosition) - vertexIn.fragPos);
			float theta = dot(lightDir,normalize(vec3(-sp.lightDirection)));

			if (theta > sp.cutOff)
			{
				//diffuse
				vec3 norm = normalize(vertexIn.normalPos);
				float diff = max(dot(norm,lightDir), 0.0f);
				vec3 diffuse = vec3(sp.lightDiffuseColor) * (diff * material[1]) * vec3(textColor);

				//specular
				vec3 viewDir = normalize(viewPos - vertexIn.fragPos);

				//blinn
				vec3 halfwayDir = normalize(lightDir + viewDir);
				float spec = pow(max(dot(vertexIn.normalPos, halfwayDir), 0.0f), materialShininess);
				vec3 specular = vec3(sp.lightSpecularColor) * (spec * material[2]);

				//attenuation
				float epsilon = sp.cutOff - sp.outerCutOff;

				if (epsilon == 0.f)
					epsilon = 0.000000001f;

				float intensity = clamp((sp.outerCutOff - theta)/epsilon, 0.0f, 1.0f);

				result += (diffuse + specular) * intensity;
			}
		}
	}

	FragColor = vec4(result, 1.0f);
}