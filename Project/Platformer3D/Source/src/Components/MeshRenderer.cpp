#include "MeshRenderer.h"
#include "ResourcesManager.h"
#include "GameObject.h"
#include "Camera.h"
#include "App.h"
#include "Light.h"

MeshRenderer::MeshRenderer(GameObject* gameObject)
{
	this->gameObject = gameObject;
}

MeshRenderer::MeshRenderer(GameObject* gameObject, std::string modelName, std::string textureName, GLuint textureMode)
{
	this->gameObject = gameObject;
	this->model = ResourceManager::Get().Get<Model>(modelName);
	this->texture = ResourceManager::Get().Get<Texture>(textureName);
	this->texture->SetMode(textureMode);
}

MeshRenderer::~MeshRenderer()
{
	model = nullptr;
	texture = nullptr;
	gameObject = nullptr;
}

void MeshRenderer::Update()
{
	if (model)
	{
		if (texture)
			texture->Bind();

		model->vertexAttributes.Bind();
		MVP = Application::Get().currentCam->GetVPMatrix() * gameObject->transform->GetGlobalTransform();
		glUniformMatrix4fv(glGetUniformLocation(Application::Get().shader.GetProgram(), "MVP"), 1, false, &MVP.col1.x); // True = transposed

		Matrix4x4 modelMatrix = gameObject->transform->GetGlobalTransform();
		glUniformMatrix4fv(glGetUniformLocation(Application::Get().shader.GetProgram(), "modelMatrix"), 1, false, &modelMatrix.col1.x);

		Vector3D campos = Application::Get().currentCam->gameObject->transform->GetGlobalPosition();
		glUniform3fv(glGetUniformLocation(Application::Get().shader.GetProgram(), "viewPos"),1, &campos[0]);

		glBufferData(GL_UNIFORM_BUFFER, sizeof(LightManagerShader), Application::Get().lightManager, GL_DYNAMIC_DRAW);
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(model->indexes.size()), GL_UNSIGNED_INT, 0);
	}
}

void MeshRenderer::Delete()
{
	delete this;
}
