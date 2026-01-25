#include "Utils/Button.h"

Button::Button(Vector3D position, Vector3D rotation, Vector3D scale, std::string texture, std::string name, Transform* parent)
{
	object = new GameObject(position, rotation, scale, texture, name, parent);

	corners = Vector4D(Application::Get().m_width * 0.5f + position.x - 0.5f * scale.x, Application::Get().m_height * 0.5f + position.y - 0.5f * scale.y, Application::Get().m_width * 0.5f + scale.x * 0.5f, Application::Get().m_height * 0.5f + scale.y * 0.5f);
}

void Button::Update()
{
	IsHovered();
	IsClicked();
}

Button* Button::GetPrevious() const
{
	return previous;
}

Button* Button::GetNext() const
{
	return next;
}

bool Button::IsHovered()
{
	hovered = false;

	if (InputHandler::GetMousePos().x >= corners.x && InputHandler::GetMousePos().x <= corners.z)
		if (InputHandler::GetMousePos().y >= corners.y && InputHandler::GetMousePos().y <= corners.w)
			hovered = true;

	return hovered;
}

bool Button::IsClicked()
{
	if (IsHovered() && InputHandler::IsMousePressed(GLFW_MOUSE_BUTTON_1))
		clicked = true;
	else
		clicked = false;

	return clicked;
}

void Button::SetPrevious(Button* value)
{
	next = value;
}

void Button::SetNext(Button* value)
{
	previous = value;
}

void Button::SetClicked(bool value)
{
	clicked = value;
}