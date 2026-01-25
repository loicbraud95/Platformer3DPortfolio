#include "Collision.h"
#include "GameObject.h"
#include "SceneGraph.h"
#include "Log.h"
#include "ResourcesManager.h"

void Collider::Update()
{
	Resize();
}

void Collider::LateUpdate()
{
}

void Collider::Delete()
{
	delete this;
}

Collider::Collider(Colliders colliderType, GameObject* _gameObject)
{
	type = colliderType;
	gameObject = _gameObject;
	oldPos = gameObject->transform->GetGlobalPosition();
}

Collider::~Collider()
{
	gameObject = nullptr;
}


SphereCollider::SphereCollider(GameObject* _gameObject)
	:Collider(Colliders::SPHERE, _gameObject)
{
	radius = 0.5f;
}

void SphereCollider::Resize()
{
	Vector3D scaleL = gameObject->transform->GetLocalScale();

	scale = scaleL.x;
	for (int i = 1; i < 3; ++i)
	{
		if (scale < scaleL[i])
			scale = scaleL[i];
	}
	scale *= 2.f;
}

BoxCollider::BoxCollider(GameObject* _gameObject)
	:Collider(Colliders::CUBE, _gameObject)
{
}

void BoxCollider::Resize()
{
	scale = gameObject->transform->GetLocalScale();
}

Collider* AddCollider(Colliders colliderType, GameObject* _gameObject)
{
	switch (colliderType)
	{
	case Colliders::SPHERE:
		return new SphereCollider(_gameObject);
		break;
	case Colliders::CUBE:
		return new BoxCollider(_gameObject);
		break;
	case Colliders::OTHER:
		break;
	}
	return nullptr;
}