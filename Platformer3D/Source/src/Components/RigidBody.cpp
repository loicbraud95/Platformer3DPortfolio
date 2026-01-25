#include "GameObject.h"
#include "IComponent.h"
#include "Utils/Time.h"

RigidBody::RigidBody(GameObject* _gameObject)
{
	gameObject = _gameObject;
}

RigidBody::~RigidBody()
{
	gameObject = nullptr;
}

void RigidBody::FixedUpdate()
{
	CheckColliders();
}

void RigidBody::Update()
{
	
}

void RigidBody::LateUpdate()
{
	if (collided)
		collided = false;
}

void RigidBody::Delete()
{
	delete this;
}

void RigidBody::CheckGrounded()
{
	isGrounded = false;
	SceneGraph::Get().root->CheckRayGroundedCollision(this);
}

void RigidBody::ApplyGravity()
{
	if (!useGravity)
		return;

	velocity += Vector3D::axeY * -GRAVITY * Time::DeltaTime();
	CheckGrounded();
}

void RigidBody::CheckColliders()
{
	colliders.clear();
	for (size_t i = 0; i < gameObject->components.size(); i++)
	{
		SphereCollider* component = dynamic_cast<SphereCollider*>(gameObject->components[i]);

		if (component != nullptr)
			colliders.push_back(component);
	}

	if (useRigidBody)
	{
		gameObject->transform->SetLocalPosition(gameObject->transform->GetLocalPosition() + velocity * Time::FixedDeltaTime());

		SceneGraph::Get().root->CheckCollision(this);

		//air friction
		if (velocity.Norm() > 0)
			velocity -= Vector3D::axeY * 25.f * Time::FixedDeltaTime();
	}

	for (size_t i = 0; i < colliders.size(); i++)
	{
		colliders[i]->oldPos = gameObject->transform->GetGlobalPosition();
	}
}




