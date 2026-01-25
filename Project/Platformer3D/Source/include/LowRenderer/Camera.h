#pragma once
#include "MathPerso.h"
#include "IComponent.h"

class GameObject;

class Camera :public IComponent
{
public:
	Camera(GameObject* _gameObject);
	~Camera() = default;

	void FixedUpdate() override {};
	void Update() override;
	void LateUpdate() override;
	void Delete() override;
	GameObject* gameObject;

	Matrix4x4 GetViewMatrix();
	Matrix4x4 GetProjectionMatrix();
	Matrix4x4 GetVPMatrix();

	void SetFov(float newFov);
	void SetNearFar(float newNear, float newFar);
	void SwitchView();

	float speed{ 10.f };
	bool recalculateView = true;
	bool recalculateProjection = true;
	bool recalculateVP = true;

private:
	Matrix4x4 viewMatrix;
	Matrix4x4 projectionMatrix;
	Matrix4x4 vpMatrix;

	float _fov{ 90.f };
	float _near{ 0.1f };
	float _far{ 1000.f };

	bool isOrtho;
};