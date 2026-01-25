#include "GameObject.h"
#include "Components.h"
#include "App.h"

int GameObject::index = 0;

GameObject::GameObject(Transform* _parent, std::string name)
{
	transform = new Transform(this, _parent);

	SetName(name);
}

GameObject::GameObject(std::string modelName, std::string textureName, std::string name, Transform* _parent, GLuint textureMode)
{
	transform = new Transform(this, _parent);

	SetName(name);

	!textureName.empty() ? components.push_back(new MeshRenderer(this, modelName, textureName, textureMode))
		: components.push_back(new MeshRenderer(this, modelName, "missing_texture.png", GL_REPEAT));

	++index;
}

GameObject::GameObject(Vector3D position, Vector3D rotation, Vector3D scale, std::string modelName, std::string textureName, std::string name, Transform* _parent, GLuint textureMode)
{
	transform = new Transform(position, rotation, scale, this, _parent);

	SetName(name);

	if (modelName != "")
	{
		!textureName.empty() ? components.push_back(new MeshRenderer(this, modelName, textureName, textureMode))
		: components.push_back(new MeshRenderer(this, modelName, "missing_texture.png", GL_REPEAT));
	}


	++index;
}

GameObject::GameObject(Vector3D position, Vector3D rotation, Vector3D scale, std::string textureName, std::string name, Transform* _parent)
{
	Vector3D nScale = Vector3D(scale.x / Application::Get().m_width * (2.f - -2.f), scale.y / Application::Get().m_height * (1.125f - -1.125f), 1);

	transform = new Transform(position, rotation, nScale, this, _parent);

	SetName(name);

	components.push_back(new MeshRenderer(this, "button.obj", textureName, GL_REPEAT));

	++index;
}

GameObject::~GameObject()
{
	for (size_t i = 0; i < components.size(); ++i)
		components[i]->Delete();

	components.clear();
	transform = nullptr;
}

void GameObject::FixedUpdate()
{
	for (size_t i = 0; i < components.size(); i++)
	{
		components[i]->FixedUpdate();
	}
}

void GameObject::Update()
{
	RigidBody* rb = GetComponent<RigidBody>();
	if (rb != nullptr)
		rb->ApplyGravity();

	for (size_t i = 0; i < components.size(); ++i)
	{
		MeshRenderer* componentMesh = dynamic_cast<MeshRenderer*>(components[i]);
		RigidBody* componentRb = dynamic_cast<RigidBody*>(components[i]);
	
		if (componentMesh == nullptr && componentRb == nullptr)
			components[i]->Update();
	}
}

void GameObject::LateUpdate()
{
	for (size_t i = 0; i < components.size(); ++i)
	{
		components[i]->LateUpdate();
	}
}

void GameObject::ResolveCollision(RigidBody* collidier)
{
	for (size_t i = 0; i < components.size(); ++i)
	{
		Collider* component = dynamic_cast<Collider*>(components[i]);
		if (component != nullptr)
		{
			for (size_t i = 0; i < collidier->colliders.size(); ++i)
			{
				SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collidier->colliders[i]);
				if (sphereCollider != nullptr)
				{
					if (CollisionSphereCollider(sphereCollider, component, collidier->velocity, collidier->fastCheck))
						collidier->collided = true;
				}
			}
		}
	}
}

void GameObject::ResolveRayGroundedCollision(RigidBody* collidier)
{
	for (size_t i = 0; i < components.size(); ++i)
	{
		Collider* component = dynamic_cast<Collider*>(components[i]);
		if (component != nullptr)
		{
			for (size_t i = 0; i < collidier->colliders.size(); ++i)
			{
				SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(collidier->colliders[i]);
				if (sphereCollider != nullptr)
				{
					Vector3D posRay = collidier->gameObject->transform->GetGlobalPosition() + Vector3D::axeY * -sphereCollider->radius * sphereCollider->scale *0.5f;
					collidier->isGrounded = RayCast(posRay, Vector3D::axeY * -sphereCollider->radius * sphereCollider->scale * 0.5f, component);
				}
			}
		}
	}
}

std::string GameObject::GetIndex() const
{
	return std::to_string(index);
}

void GameObject::AddComponent(IComponent* newComponent)
{
	if (newComponent)
		components.push_back(newComponent);
}

void GameObject::SetName(std::string name)
{
	if (name.empty())
		name = "GameObject " + GetIndex();

	transform->SetName(name);
}
