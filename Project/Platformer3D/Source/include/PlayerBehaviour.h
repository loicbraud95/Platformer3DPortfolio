#pragma once

#include "IComponent.h"
#include "Utils/InputHandler.h"

class GameObject;
class RigidBody;

class PlayerBehaviour : public IComponent
{
public:
	PlayerBehaviour(GameObject* _gameObject);
	PlayerBehaviour() = default;
	~PlayerBehaviour() = default;

	void FixedUpdate() override {};
	void Update() override;
	void LateUpdate() override;
	void Delete() override;


	bool jump = false;
	int nbJump = 2;
	GameObject* gameObject;
	RigidBody* rb;
	void Jump(int key);
	void Bind();

	Vector3D respawnPoint = Vector3D(0, 20, 0);

	bool oldGrounded = false;
private:
	enum State
	{
		IDLE,
		MOVE,
		JUMPING,
		FALLING
	};
};