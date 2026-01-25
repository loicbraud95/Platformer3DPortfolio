#include "Menus/ControlsMenu.h"

void ControlsMenu::Init()
{
}

void ControlsMenu::Draw()
{
	DrawMenu();
}

void ControlsMenu::DrawMenu()
{
	ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
	if (ImGui::Begin("ChildR"), ImGuiWindowFlags_AlwaysAutoResize)
	{
		if (ImGui::BeginTable("split", 1, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings))
		{
			for (auto ch = InputHandler::keyMapping.begin(); ch != InputHandler::keyMapping.end(); ++ch)
			{
				const char* keyName = glfwGetKeyName(ch->first, 0);

				ImGui::TableNextColumn();
				ImGui::Button(keyName, ImVec2(-FLT_MIN, 0.0f));
			}
			ImGui::EndTable();
		}
	}
	ImGui::End();
	ImGui::PopStyleVar();
}