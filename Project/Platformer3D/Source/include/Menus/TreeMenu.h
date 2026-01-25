#pragma once

#include "Scene/Transform.h"
#include "Scene/SceneGraph.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

class TreeMenu
{
public:
	TreeMenu() = default;

	void Draw();

	~TreeMenu() = default;
private:

	void DrawRoot();
	void DrawChildren(Transform* child);
	static void DrawChildSettings(Transform* child);
	void DrawButton(Transform* child);

	Transform* latestChildClicked;
};