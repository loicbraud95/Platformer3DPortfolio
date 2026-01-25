#include "GameObject.h"

Transform::Transform(bool isRoot)
{
	gameObject = nullptr;
	name = "root";
	if(!isRoot)
		SetParent(SceneGraph::Get().root);

	SetZero();
}

Transform::Transform(GameObject* _gameObject)
{
	if (_gameObject)
		gameObject = _gameObject;

	SetParent(SceneGraph::Get().root);

	SetZero();
}

Transform::Transform(GameObject* _gameObject, Transform* _parent)
{
	if (_gameObject)
		gameObject = _gameObject;

	if (_parent)
		SetParent(_parent);
	else
		SetParent(SceneGraph::Get().root);

	SetZero();
}

Transform::Transform(Vector3D position, Vector3D rotation, Vector3D scale, GameObject* _gameObject, Transform* _parent)
{
	if (_gameObject)
		gameObject = _gameObject;

	if (_parent)
		SetParent(_parent);
	else
		SetParent(SceneGraph::Get().root);

	localPosition = position;
	localRotation = rotation;
	localScale = scale;

	recalculateLocalT = true;
	GetLocalTransform();
	GetGlobalTransform();
}

Transform::~Transform()
{
	if(gameObject != nullptr)
		delete gameObject;

	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->Delete();
		--i;
	}

	if (parent)
		parent->RemoveChildren(this);
	children.clear();
}

void Transform::SetZero()
{
	localPosition = Vector3D::zero;
	localRotation = Vector3D::zero;
	localScale = Vector3D::one;

	localTransform = Identity_Matrix4x4();
	globalTransform = Identity_Matrix4x4();
}

void Transform::FixedUpdate()
{
	if (gameObject)
	{
		if (!gameObject->enable)
			return;
		gameObject->FixedUpdate();
	}

	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->gameObject->transform->FixedUpdate();
	}
}

void Transform::Update()
{
	if (gameObject)
	{
		if (!gameObject->enable)
			return;
		gameObject->Update();
	}

	for (size_t i = 0; i < children.size(); i++)
		children[i]->gameObject->transform->Update();
}

void Transform::LateUpdate()
{
	if (gameObject)
	{
		if (!gameObject->enable)
			return;
		gameObject->LateUpdate();
	}

	for (size_t i = 0; i < children.size(); i++)
		children[i]->gameObject->transform->LateUpdate();
}

void Transform::Render()
{
	if (gameObject)
	{
		if (!gameObject->enable)
			return;

		MeshRenderer* mesh = gameObject->GetComponent<MeshRenderer>();

		if (mesh)
			mesh->Update();
	}

	for (size_t i = 0; i < children.size(); i++)
		children[i]->gameObject->transform->Render();
}

void Transform::Delete()
{
	delete this;
}

void Transform::CheckCollision(RigidBody* collider)
{
	if (gameObject && gameObject != collider->gameObject)
	{
		if (!gameObject->enable)
			return;

		gameObject->ResolveCollision(collider);
	}

	for (size_t i = 0; i < children.size(); i++)
		children[i]->gameObject->transform->CheckCollision(collider);
}

void Transform::CheckRayGroundedCollision(RigidBody* collider)
{
	if (collider->isGrounded == true)
		return;

	if (gameObject && gameObject != collider->gameObject)
	{
		if (!gameObject->enable)
			return;
		gameObject->ResolveRayGroundedCollision(collider);
	}

	for (size_t i = 0; i < children.size(); i++)
		children[i]->gameObject->transform->CheckRayGroundedCollision(collider);
}

void Transform::SetParent(Transform* _parent)
{
	if (parent != nullptr)
		parent->RemoveChildren(this);

	parent = _parent;

	if (parent == nullptr)
		parent = SceneGraph::Get().root;

	parent->AddChildren(this);

	SetLocalTransformOnParentChange();
}

void Transform::SetChildrenRecalculateGlobalTransform()
{
	for (size_t i = 0; i < children.size(); i++)
	{
		children[i]->recalculateGlobalT = true;
		children[i]->SetChildrenRecalculateGlobalTransform();
	}
}

void Transform::AddChildren(Transform* child)
{
	if (child == nullptr)
		return;

	child->recalculateGlobalT = true;

	children.push_back(child);
}

void Transform::RemoveChildren(Transform* child)
{
	for (size_t i = 0; i < children.size(); i++)
		if (children[i] == child)
		{
			children[i]->parent = nullptr;
			children.erase(children.begin() + i);
			return;
		}
}

#pragma region Local Transform

void Transform::SetLocalTransformOnParentChange()
{
	//check if every thing is up to date
	recalculateGlobalT = false;

	Matrix4x4 reverseParentRotation_G = Reverse(Rotation_Matrix4x4(parent->GetGlobalRotation()));
	Matrix4x4 reverseParentScale_G = Reverse(Scaling_Matrix4x4(parent->GetGlobalScale()));

	localRotation = reverseParentRotation_G * static_cast<Vector4D>(GetGlobalRotation());
	localScale = reverseParentScale_G * static_cast<Vector4D>(GetGlobalScale());
	localPosition = reverseParentScale_G * reverseParentRotation_G * static_cast<Vector4D>(GetGlobalPosition() - parent->GetGlobalPosition());

	recalculateLocalT = true;
	GetLocalTransform();
	GetGlobalTransform();

	SetChildrenRecalculateGlobalTransform();
}

Matrix4x4 Transform::GetLocalTransform()
{
	if (recalculateLocalT)
	{
		recalculateLocalT = false;
		recalculateGlobalT = true;
		localTransform = TRS(localPosition,localRotation,localScale);
	}

	return localTransform;
}

std::string Transform::GetName() const
{
	return name;
}

void Transform::SetName(std::string value)
{
	name = value;
}

std::vector<Transform*>& Transform::GetChildren()
{
	return children;
}

Vector3D Transform::GetLocalPosition()
{
	return localPosition;
}

void Transform::SetLocalPosition(Vector3D newPosition)
{
	localPosition = newPosition;
	recalculateLocalT = true;

	SetChildrenRecalculateGlobalTransform();
}

Vector3D Transform::GetLocalRotation()
{
	return localRotation;
}

void Transform::SetLocalRotation(Vector3D newRotation)
{
	if (newRotation.x >= 360.f || newRotation.x <= -360.f)
		newRotation.x = 0.f;

	if (newRotation.y >= 360.f || newRotation.y <= -360.f)
		newRotation.y = 0.f;

	if (newRotation.z >= 360.f || newRotation.z <= -360.f)
		newRotation.z = 0.f;

	localRotation = newRotation;
	recalculateLocalT = true;

	SetChildrenRecalculateGlobalTransform();
}

Vector3D Transform::GetLocalScale()
{
	return localScale;
}

void Transform::SetLocalScale(Vector3D newScale)
{
	localScale = newScale;
	recalculateLocalT = true;

	SetChildrenRecalculateGlobalTransform();
}
#pragma endregion

#pragma region Global Transform

Matrix4x4 Transform::GetGlobalTransform()
{
	if (parent == nullptr)
		return localTransform;

	if (recalculateLocalT)
		GetLocalTransform();

	if (recalculateGlobalT)
	{
		recalculateGlobalT = false;
		globalTransform = parent->GetGlobalTransform() * localTransform;

		GetGlobalPosition();
		GetGlobalRotation();
		GetGlobalScale();
	}

	return globalTransform;
}

Vector3D Transform::GetGlobalPosition()
{
	globalPosition = GetGlobalTransform().col4;
	return globalPosition;
}

void Transform::SetGlobalPosition(Vector3D newPosition)
{
	Vector3D pos = newPosition - gameObject->transform->GetGlobalPosition();
	gameObject->transform->SetLocalPosition(gameObject->transform->GetLocalPosition() + pos);
}

Vector3D Transform::GetGlobalRotation()
{
	if (parent == nullptr)
		return localRotation;

	globalRotation = localRotation + parent->GetGlobalRotation();
	return globalRotation;
}

Vector3D Transform::GetGlobalScale()
{
	if (parent == nullptr)
		return localScale;

	globalScale = TensorialProduct(localScale,parent->GetGlobalScale());
	return globalScale;
}
Vector3D Transform::GetForward()
{
	Vector3D forward = Rotation_Matrix4x4(gameObject->transform->GetGlobalRotation() * (PI / 180.f)) * (Vector4D)Vector3D::axeZ;
	forward.Normalize();
	return forward;
}
Vector3D Transform::GetRight()
{
	Vector3D right = Rotation_Matrix4x4(gameObject->transform->GetGlobalRotation() * (PI / 180.f)) * (Vector4D)Vector3D::axeX;
	right.Normalize();
	return right;
}
Vector3D Transform::GetUp()
{
	Vector3D up = Rotation_Matrix4x4(gameObject->transform->GetGlobalRotation() * (PI / 180.f)) * (Vector4D)Vector3D::axeY;
	up.Normalize();
	return up;
}

void Transform::SetScreenPosition(float x, float y, float z)
{
	screenPosition = { x, y, z };
}

void Transform::SetScreenRotation(float x, float y, float z)
{
	screenRotation = { x, y, z };
}

void Transform::SetScreenScale(float width, float height)
{
	screenScale = { width, height };
}

Vector3D Transform::GetScreenPosition() const
{
	return screenPosition;
}

Vector3D Transform::GetScreenRotation()
{
	return screenRotation;
}

Vector3D Transform::GetScreenScale()
{
	return screenScale;
}

#pragma endregion