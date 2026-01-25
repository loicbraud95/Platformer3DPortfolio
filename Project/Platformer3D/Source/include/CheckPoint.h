#pragma once
#include "IComponent.h"
#include "Collider.h"

class PlayerBehaviour;
class GameObject;
class RigidBody;

class CheckPoint : public IComponent
{
public:
	CheckPoint(GameObject* _gameObject,GameObject* _objToActivate, PlayerBehaviour* _player);
	~CheckPoint() = default;

	void FixedUpdate() override {};
	void Update() override;
	void LateUpdate() override {};
	void Delete() override;

	GameObject* gameObject;
	GameObject* objectToActivate;

	PlayerBehaviour* player;

	SphereCollider* collider;
	SphereCollider* playerCollider;

private:

};
