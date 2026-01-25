#pragma once

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "App.h"
#include "Menus/TreeMenu.h"
#include "Menus/ControlsMenu.h"

class Menu
{
public:
	~Menu() = default;

	static Menu& Get();
	static void Destroy();

	void Init();
	void Render();
	void Draw();

private:
	Menu() = default;

	static Menu* instance;

	TreeMenu* tree;
	ControlsMenu* controls;

};