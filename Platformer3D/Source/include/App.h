#pragma once

#include "MathPerso.h"
#include "Shader.h"
#include "Utils/WindowHandler.h"
#include "Light.h"
#include "Utils/InputHandler.h"
#include "Model.h"
#include "Camera.h"
#include "Utils/Time.h"
#include "SceneGraph.h"
#include "Resources/Texture.h"
#include "GameObject.h"
#include "Menu.h"

enum class MenuState
{
	MAINMENU,
	SETTINGS,
	PAUSE,
	PLAYING
};

class Button;
class Application
{
public:
	~Application();
	LightManagerShader* lightManager;

	static Application& Get();
	static void Destroy();

	static Vector2D oldMousePos;

	GLFWwindow* window;
	Shader shader;

	Camera* currentCam = nullptr;
	Camera* oldCam = nullptr;

	int32_t m_width = 1280;
	int32_t m_height = 720;

	bool Initialise();
	void Update();
	void Render();
	void SwitchView();

private:
	static Application* instance;
	Application() = default;

	void InitShaders();
	void InitResources();
	void InitCallbacks();

	void HandleInputs();
	void HandleMouseInputs(Camera* cam);

	// Game Related
	void InitGame();

	PlayerBehaviour* InitPlayer();

	GameObject* InitLevel0();
	GameObject* InitLevel1();
	GameObject* InitLevel2();
	GameObject* InitEndLevel();

	// Button Related
	void InitButtons();
	void UpdateButtons();
	void DestroyButtons();

	std::vector<Button*> buttons;
	MenuState state = MenuState::PLAYING;
};