#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Vector.h"
#include "GameObject.h"
#include "Transform.h"
#include "App.h"

#include <vector>
#include <string>

class Button
{
public:
	Button() = default;
	Button(Vector3D position, Vector3D rotation, Vector3D scale, std::string texture, std::string name, Transform* parent = Application::Get().oldCam->gameObject->transform);

	~Button() = default;

	void Update();

	Button* GetPrevious() const;
	Button* GetNext() const;
	bool IsHovered();
	bool IsClicked();

	void SetPrevious(Button* value);
	void SetNext(Button* value);
	void SetClicked(bool value);

private:
	Vector4D corners;
	Button* previous = nullptr;
	Button* next = nullptr;

	GameObject* object = nullptr;

	bool hovered = false;
	bool clicked = false;
};