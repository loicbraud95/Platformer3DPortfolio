#include "Menus/TreeMenu.h"
#include "GameObject.h"
void TreeMenu::DrawRoot()
{
	ImGui::Indent(20.0f);

	for (auto ch = SceneGraph::Get().root->GetChildren().begin(); ch != SceneGraph::Get().root->GetChildren().end(); ++ch)
		DrawChildren((*ch));

	ImGui::Unindent(20.0f);
}

void TreeMenu::Draw()
{
	ImGui::SetNextWindowSize(ImVec2(400.f, 250.f), ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2(0.f, 0.f), ImGuiCond_Once);

	// Object Tree Window
	if (ImGui::Begin("Object Tree"), ImGuiWindowFlags_AlwaysAutoResize)
		if (ImGui::CollapsingHeader("Scene"))
			DrawRoot();

	if (latestChildClicked != nullptr)
		DrawChildSettings(latestChildClicked);

	ImGui::End();
}

void TreeMenu::DrawButton(Transform* child)
{
	ImGui::Button((child->GetName()).c_str());
	if (ImGui::IsItemClicked())
		latestChildClicked = child;
}

void TreeMenu::DrawChildren(Transform* child)
{
	ImGui::Indent(20.0f);

	if (child->GetChildren().empty())
	{
		DrawButton(child);
		ImGui::Unindent(20.0f);
		return;
	}
	else
	{
		if (ImGui::CollapsingHeader((child->GetName()).c_str()))
		{
			ImGui::Indent(20.0f);
			DrawButton(child);

			for (auto ch = child->GetChildren().begin(); ch != child->GetChildren().end(); ++ch)
				DrawChildren((*ch));

			ImGui::Unindent(20.0f);
		}
	}

	ImGui::Unindent(20.0f);
}

void TreeMenu::DrawChildSettings(Transform* child)
{
	std::string title = "Object Inspector : " + child->GetName() + "###inspector";
	ImGui::SetNextWindowSize(ImVec2(400.f, 250.f), ImGuiCond_Once);
	ImGui::SetNextWindowPos(ImVec2(0.f, 275.f), ImGuiCond_Once);

	if (ImGui::Begin(title.c_str()), ImGuiWindowFlags_AlwaysAutoResize)
	{
		Vector3D translationF = child->GetLocalPosition();
		Vector3D rotationF = child->GetLocalRotation();
		Vector3D scalingF = child->GetLocalScale();

		ImGui::DragFloat3(("translationXY##" + child->GetName()).c_str(), &translationF[0], 0.1f);
		ImGui::DragFloat3(("rotationXYZ##" + child->GetName()).c_str(), &rotationF[0], 0.1f);
		ImGui::DragFloat3(("scalingXYZ##" + child->GetName()).c_str(), &scalingF[0], 0.1f, 0.2f);

		if (translationF != child->GetLocalPosition())
			child->SetLocalPosition(translationF);

		if (rotationF != child->GetLocalRotation())
			child->SetLocalRotation(rotationF);

		if (scalingF != child->GetLocalScale())
			child->SetLocalScale(scalingF);

		bool enableB = child->gameObject->enable;
		std::string enableTxt = "";
		if (enableB)
			enableTxt = "set false";
		else
			enableTxt = "set true";

		ImGui::Button((enableTxt).c_str());
		if (ImGui::IsItemClicked())
			child->gameObject->enable = !child->gameObject->enable;

	} ImGui::End();
}