#pragma once

#include "Scene/Transform.h"
#include "Scene/SceneGraph.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Utils/InputHandler.h"

class ControlsMenu
{
public:
	ControlsMenu() = default;

	void Init();
	void Draw();

	~ControlsMenu() = default;
private:

	void DrawMenu();
};