#include "CheckPoint.h"
#include "GameObject.h"
#include "RigidBody.h"
#include "PlayerBehaviour.h"
#include "Collision.h"

CheckPoint::CheckPoint(GameObject* _gameObject, GameObject* _objToActivate , PlayerBehaviour* _player)
{
	objectToActivate = _objToActivate;

	gameObject = _gameObject;
	player = _player;
	playerCollider = player->gameObject->GetComponent<SphereCollider>();

	collider = gameObject->GetComponent<SphereCollider>();
}

void CheckPoint::Update()
{
	if(CollisionSphereSphere(collider, playerCollider))
	{
		objectToActivate->enable = true;
		player->respawnPoint = gameObject->transform->GetGlobalPosition() + Vector3D::axeY * 35.f;
	}
}

void CheckPoint::Delete()
{
	delete this;
}