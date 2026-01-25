#pragma once
#include "MathPerso.h"
#include "Collision.h"
#include <vector>

class GameObject;
class RigidBody;

class Transform
{
public:
	Transform(bool root = false);
	Transform(GameObject* _gameObject);
	Transform(GameObject* _gameObject,Transform* _parent);
	Transform(Vector3D position,Vector3D rotation,Vector3D scale,GameObject* _gameObject, Transform* _parent);
	Transform(Vector2D position, Vector2D rotation, Vector2D scale, GameObject* _gameObject, Transform* _parent);
	~Transform();
	void SetZero();

	void FixedUpdate();
	void Update();
	void LateUpdate();
	void Render();
	void Delete();

	void CheckCollision(RigidBody* collider);
	void CheckRayGroundedCollision(RigidBody* collider);

	void SetParent(Transform* parent);
	void SetChildrenRecalculateGlobalTransform();

	GameObject* gameObject = nullptr;

	#pragma region Local Get/Set
	
	Matrix4x4 GetLocalTransform();

	Vector3D GetLocalPosition();
	void SetLocalPosition(Vector3D newPosition);
	
	Vector3D GetLocalRotation();
	void SetLocalRotation(Vector3D newRotation);
	
	Vector3D GetLocalScale();
	void SetLocalScale(Vector3D newScale);
	#pragma endregion

	#pragma region Global Get

	Matrix4x4 GetGlobalTransform();

	Vector3D GetGlobalPosition();
	void SetGlobalPosition(Vector3D newPosition);

	Vector3D GetGlobalRotation();
	Vector3D GetGlobalScale();

	Vector3D GetForward();
	Vector3D GetRight();
	Vector3D GetUp();
	#pragma endregion

#pragma region Screen Get/Set
	void SetScreenPosition(float x, float y, float z);
	void SetScreenRotation(float x, float y, float z);
	void SetScreenScale(float width, float height);

	Vector3D GetScreenPosition() const;
	Vector3D GetScreenRotation();
	Vector3D GetScreenScale();
#pragma endregion

	std::string GetName() const;
	void SetName(std::string value);

	std::vector<Transform*>& GetChildren();

	bool recalculateLocalT = true;
	bool recalculateGlobalT = true;

private :
	void SetLocalTransformOnParentChange();
	void AddChildren(Transform* child);
	void RemoveChildren(Transform* child);
	std::vector<Transform*> children;

	Matrix4x4 localTransform;
	Matrix4x4 globalTransform;
	
	Vector3D localPosition;
	Vector3D localRotation;
	Vector3D localScale;

	Vector3D globalPosition;
	//local rota + parent rota + parent parent rota (+ parent global rota en gros)
	Vector3D globalRotation;
	//local scale * parent local scale * ...
	Vector3D globalScale;

	Vector3D screenPosition;
	Vector3D screenRotation;
	Vector3D screenScale;

	Transform* parent = nullptr;
	std::string name = "";
};

