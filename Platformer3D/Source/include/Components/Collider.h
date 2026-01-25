#pragma once
#include "IComponent.h"
#include "MathPerso.h"

class GameObject;

enum class Colliders
{
	SPHERE,
	CUBE,
	OTHER
};

class Collider : public IComponent
{
public:
	void FixedUpdate() override {};
	void Update() override;
	void LateUpdate() override;
	void Delete() override;

	virtual void Resize() = 0;
	Colliders type;

	GameObject* gameObject;
	Vector3D oldPos;

protected:
	Collider(Colliders colliderType, GameObject* _gameObject);
	~Collider();
};

class SphereCollider : public Collider
{
public:
	SphereCollider(GameObject* _gameObject);
	~SphereCollider() = default;

	void Resize() override;

	float scale = 0.f;
	float radius = 0.5f;
};

class BoxCollider : public Collider
{
public:
	BoxCollider(GameObject* _gameObject);
	~BoxCollider() = default;

	void Resize() override;
	Vector3D scale = { 1,1,1 };
	Vector3D size = { 1,1,1 };
};

Collider* AddCollider(Colliders colliderType, GameObject* _gameObject);