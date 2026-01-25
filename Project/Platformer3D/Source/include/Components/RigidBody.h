#pragma once
#include "IComponent.h"
#include "Collider.h"
#include <vector>

class RigidBody : public IComponent
{
public:
	RigidBody(GameObject* _gameObject);
	~RigidBody();

	void FixedUpdate() override;
	void Update() override;
	void LateUpdate() override;
	void Delete() override;

	void ApplyGravity();

	void CheckColliders();

	GameObject* gameObject;
	std::vector<Collider*> colliders;

	bool useRigidBody = true;
	bool fastCheck = false;
	bool useGravity = true;
	bool isGrounded = false;
	bool collided = false;
	Vector3D velocity;
private:
	void CheckGrounded();

};