#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "MathPerso.h"
#include "IComponent.h"

class GameObject;

/////////////// Shader Lights ///////////////

enum class DirectionalLights
{
	DIR0,
	DIR1,
	DIR2,
	DIR3,
	NbLight
};

enum class PointLigths
{
	PT0,
	PT1,
	PT2,
	PT3,
	NbLight
};

enum class SpotLights
{
	SP0,
	SP1,
	SP2,
	SP3,
	NbLight
};

struct DirectionalLight
{
	Vector4D lightDirection;

	Vector4D lightAmbientColor;
	Vector4D lightDiffuseColor;
	Vector4D lightSpecularColor;

	int enable = 0;
	int filling1 = 0;
	int filling2 = 0;
	int filling3 = 0;
};

struct PointLight
{
	Vector4D lightPosition;

	Vector4D lightAmbientColor;
	Vector4D lightDiffuseColor;
	Vector4D lightSpecularColor;

	float constant;
	float linear;
	float quadratic;
	int enable;
};

struct SpotLight
{
	Vector4D lightPosition;
	Vector4D lightDirection;

	Vector4D lightAmbientColor;
	Vector4D lightDiffuseColor;
	Vector4D lightSpecularColor;


	float cutOff;
	float outerCutOff;
	int enable;
	int filling3;
};

struct LightManagerShader
{
	DirectionalLight directional[4];
	PointLight points[4];
	SpotLight spots[4];

	GLuint ubo;
	float filling1;
	float filling2;
	float filling3;

	void SetLight(DirectionalLights lightToSet, Vector4D direction, Vector4D ambientColor,Vector4D diffuseColor,Vector4D specularColor,bool enable);
	void SetLight(PointLigths lightToSet, Vector4D position, Vector4D ambientColor, Vector4D diffuseColor, Vector4D specularColor
		, float constant, float linear, float quadratic, bool enable);
	void SetLight(SpotLights lightToSet, Vector4D position, Vector4D direction, Vector4D ambientColor, Vector4D diffuseColor, Vector4D specularColor
		, float cutOff, float outerCutOff, bool enable);

	void SetActive(DirectionalLights lightToSet, bool enable);
	void SetActive(PointLigths lightToSet, bool enable);
	void SetActive(SpotLights lightToSet, bool enable);
	void SetSpotAngle(SpotLights lightToSet,float angleInDegree,bool add = false);
	void SetSpotOuterCutOff(SpotLights lightToSet, float angleInDegree);
	float GetSpotAngle(SpotLights lightToSet);


	void SetUpDirectional();
	void SetUpPoints();
	void SetUpSpots();
	void Init();
};

/////////////////////////////////////////////

/////////////// Game Lights ///////////////

class GameLight : public IComponent
{
public:
	GameLight(GameObject* _gameObject);
	~GameLight();

	GameObject* gameObject;

	Vector3D LightColor;
	Vector3D lightAmbient;
	Vector3D lightDiffuse;
	Vector3D lightSpecular;

	bool enable = false;

	void FixedUpdate() override {};
	void Update()override {};
	void LateUpdate()override {};
	void Delete();
};

class GamePointLight : public GameLight
{
public:
	GamePointLight(GameObject* _gameObject,float _quadratic = 0, float _linear = 0 , float _constant = 1);
	~GamePointLight() = default;

	Vector3D lightPosition;
	float constant;
	float linear;
	float quadratic;
};

class GameDirectionalLight : public GameLight
{
public:
	GameDirectionalLight(GameObject* _gameObject);
	~GameDirectionalLight() = default;

	Vector3D lightDirection;

};

class GameSpotLight : public GameLight
{
public:
	GameSpotLight(GameObject* _gameObject, Vector3D _position = Vector3D::zero, Vector3D _direction = Vector3D::axeY * -1.f, float _cutOff = 45.f, float _outerCutOff = 30.f);
	~GameSpotLight() = default;

	Vector3D lightPosition;
	Vector3D lightDirection;

	float cutOff;
	float outerCutOff;
};

/////////////////////////////////////////////