#include "App.h"
#include "Utils/Button.h"
#include "Menu.h"

Vector2D Application::oldMousePos = { 0.f,0.f };
Application* Application::instance = nullptr;

Application::~Application()
{
	if (instance->lightManager)
	{
		delete instance->lightManager;
		instance->lightManager = nullptr;
	}

	if (!instance->buttons.empty())
		DestroyButtons();
}

Application& Application::Get()
{
	if (instance == nullptr)
		instance = new Application();
	return *instance;
}

void Application::Destroy()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void Application::InitShaders()
{
	/* DEFAULT SHADER */
	shader.SetVertex("Assets/Shaders/Default.vert");
	shader.SetFragment("Assets/Shaders/Default.frag");
	shader.Link();

	glGenBuffers(1, &instance->lightManager->ubo);
	glBindBuffer(GL_UNIFORM_BUFFER, instance->lightManager->ubo);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(LightManagerShader), lightManager, GL_DYNAMIC_DRAW);

	unsigned int index = glGetUniformBlockIndex(shader.GetProgram(), "Lights");
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, instance->lightManager->ubo);
}

void Application::InitCallbacks()
{
	/* Handle Keyboard & Mouse Inputs */
	glfwSetKeyCallback(Application::window, InputHandler::KeyboardCallback);
	glfwSetCursorPosCallback(Application::window, InputHandler::MouseCursorCallback);
	glfwSetMouseButtonCallback(Application::window, InputHandler::MouseButtonCallback);
	glfwSetScrollCallback(Application::window, InputHandler::MouseScrollCallback);

	/* Window resizing & framebuffer callbacks */
	glfwSetFramebufferSizeCallback(Application::window, WindowHandler::BufferResizeCallback);
	glfwSetWindowSizeCallback(Application::window, WindowHandler::WindowResizeCallback);
}

void InitModel(std::string modelName)
{
	Model* model = ResourceManager::Get().Create<Model>(modelName);

	if (model == nullptr)
	{
		DEBUG_LOG("The model (" + modelName + ") doesn't exists!");
		return;
	}

	model->vertexAttributes.Bind();

	model->vbo.Bind(GL_ARRAY_BUFFER);
	model->vbo.SetData(GL_ARRAY_BUFFER, sizeof(Vertex) * model->vertices.size(), model->vertices.data(), GL_STATIC_DRAW);

	model->ebo.Bind(GL_ELEMENT_ARRAY_BUFFER);
	model->ebo.SetData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * model->indexes.size(), model->indexes.data(), GL_STATIC_DRAW);
	model->vertexAttributes.SetAttributes(0, 3, GL_FLOAT, false, sizeof(Vertex), (void*)(0));
	model->vertexAttributes.SetAttributes(1, 2, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::textureUV));
	model->vertexAttributes.SetAttributes(2, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, Vertex::normal));
}

void InitTexture(std::string textureName)
{
	Texture* texture = ResourceManager::Get().Create<Texture>(textureName);

	if (texture == nullptr)
	{
		DEBUG_LOG("The model (" + textureName + ") doesn't exists!");
		return;
	}
}

 void Application::InitResources()
{
	std::string path = "Assets/Meshes/";
	std::string txtPath = "Assets/Textures/";

	for (const auto& entry : std::filesystem::directory_iterator(path))
		InitModel(entry.path().filename().string());

	for (const auto& txtEntry : std::filesystem::directory_iterator(txtPath))
		InitTexture(txtEntry.path().filename().string());
}

bool Application::Initialise()
{
	lightManager = new LightManagerShader();
	lightManager->Init();

	InitResources();
	InitCallbacks();
	InitShaders();
	InitGame();

	return true;
}

void Application::InitButtons()
{
	Button* resume = new Button({ 0.f, 0.25f, -1.f }, Vector3D::zero, { 300.f, 100.f, 1.f }, "resume.png", "resume");
	Button* quit = new Button({ 0.f, 0.75f, -1.f }, Vector3D::zero, { 300.f, 100.f, 1.f }, "quit.png", "b1");

	buttons.push_back(resume);
	buttons.push_back(quit);
}

void Application::UpdateButtons()
{
	for (int i = 0; i < buttons.size(); ++i)
		buttons[i]->Update();
}

void Application::DestroyButtons()
{
	for (int i = 0; i < buttons.size(); ++i)
		delete buttons[i];

	buttons.clear();
}

void Application::Update()
{
	Time::Update();
	if (Time::DeltaTime() < 1.f)
	{
		Time::timer += Time::DeltaTime();
		while (Time::timer >= Time::FixedDeltaTime())
		{
			SceneGraph::Get().FixedUpdate();
			Time::timer -= Time::FixedDeltaTime();
		}

		SceneGraph::Get().Update();
		SceneGraph::Get().LateUpdate();
		HandleInputs();

		Render();
	}
	UpdateButtons();
}

void Application::HandleInputs()
{
	if (instance->currentCam)
		HandleMouseInputs(instance->currentCam);
}

void Application::Render()
{
	glViewport(0, 0, m_width, m_height);
	glClearColor(0.07f, 0.57f, 0.99f, 1.f); // Set background color to blue
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(shader.GetProgram());
	SceneGraph::Get().Render();
	Menu::Get().Render();
}

void Application::HandleMouseInputs(Camera* cam)
{
	instance->oldMousePos = InputHandler::GetMousePos();
}

PlayerBehaviour* Application::InitPlayer()
{
	GameObject* player = new GameObject({ 0,20,0 }, { 0,0,0 }, Vector3D::one * 1.5f, "", "", "player");
	GameObject* modelPlayer = new GameObject({ 0.f,-1.f,0.f }, { 0.f,180.f,0.f }, Vector3D::one * 0.1f, "Alien.obj", "alien.png", "model player", player->transform);
	Collider* colliderPlayer = AddCollider(Colliders::SPHERE, player);
	SphereCollider* sphereCollider = dynamic_cast<SphereCollider*>(colliderPlayer);
	sphereCollider->radius = 0.5f;
	player->AddComponent(colliderPlayer);
	RigidBody* rb = new RigidBody(player);
	rb->fastCheck = true;
	rb->useGravity = true;
	player->AddComponent(rb);
	PlayerBehaviour* playerBehaviour = new PlayerBehaviour(player);
	player->AddComponent(playerBehaviour);
	playerBehaviour->Bind();

	GameObject* cam = new GameObject(player->transform, "main camera");
	cam->transform->SetLocalPosition(Vector3D(0.f, 9.5f, 10.5f));
	cam->transform->SetLocalRotation(Vector3D(-25.f, 0.f, 0.f));
	cam->AddComponent(new Camera(cam));

	GameObject* menuCam = new GameObject(nullptr, "second camera");
	menuCam->transform->SetLocalPosition(Vector3D(0.f, -500.f, 0.f));
	Camera* camComponent = new Camera(menuCam);
	menuCam->AddComponent(camComponent);
	Application::Get().oldCam = camComponent;

	return playerBehaviour;
}

void Application::InitGame()
{
	GameObject* debugContainer = new GameObject(nullptr, "debugContainer");

	PlayerBehaviour* playerB = InitPlayer();

	GameObject* lvl0 = InitLevel0();
	GameObject* lvl1 = InitLevel1();
	GameObject* lvl2 = InitLevel2();
	GameObject* endLvl = InitEndLevel();

	InitButtons();

	GameObject* respawn1 = new GameObject({ 0,5,-120 }, { 0.f,0,0 }, { 10,4,10 }, "", "", "respawn 1");
	respawn1->AddComponent(AddCollider(Colliders::SPHERE, respawn1));
	CheckPoint* checkpt1 = new CheckPoint(respawn1, lvl1, playerB);
	respawn1->AddComponent(checkpt1);

	GameObject* respawn2 = new GameObject({ 40.f,73.f,-122.5 }, { 0.f,0.f,0.f }, { 10,4,10 }, "", "", "respawn 2");
	respawn2->AddComponent(AddCollider(Colliders::SPHERE, respawn2));
	CheckPoint* checkpt2 = new CheckPoint(respawn2, lvl2, playerB);
	respawn2->AddComponent(checkpt2);

	GameObject* respawn3 = new GameObject({ 220.f,70.f,-122.5f }, { 0.f,0.f,0.f }, { 20,4,20 }, "", "", "respawn 3");
	respawn3->AddComponent(AddCollider(Colliders::SPHERE, respawn3));
	CheckPoint* checkpt3 = new CheckPoint(respawn3, endLvl, playerB);
	respawn3->AddComponent(checkpt3);
}

GameObject* Application::InitLevel0()
{
	GameObject* lvl0 = new GameObject(nullptr, "lvl0");

	GameObject* ground = new GameObject({ 0,-10,0 }, { 0,0,0 }, { 30,20,30 }, "cube.obj", "grass.png", "ground", lvl0->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	ground = new GameObject({ 0,-5,-35 }, { 0,0,0 }, { 10,7,10 }, "cube.obj", "grass.png", "ground", lvl0->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	ground = new GameObject({ 0,2,-50 }, { 0,0,0 }, { 10,4,10 }, "cube.obj", "grass.png", "ground", lvl0->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	ground = new GameObject({ -15,2,-70 }, { 0,0,0 }, { 10,4,10 }, "cube.obj", "grass.png", "ground", lvl0->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	ground = new GameObject({ 10,2,-85 }, { 0,0,0 }, { 10,4,10 }, "cube.obj", "grass.png", "ground", lvl0->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	ground = new GameObject({ 0,2,-100 }, { 30.f,0,0 }, { 10,4,10 }, "cube.obj", "grass.png", "ground", lvl0->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	ground = new GameObject({ 0,5,-120 }, { 0.f,0,0 }, { 10,4,10 }, "cube.obj", "grass.png", "ground", lvl0->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	return lvl0;
}

GameObject* Application::InitLevel1()
{
	GameObject* lvl1 = new GameObject(nullptr, "lvl1");
	lvl1->enable = false;

	GameObject* ground = new GameObject({ 15,10,-135 }, { 0.f,45.f,20.f }, { 10,4,10 }, "cube.obj", "rock.png", "ground", lvl1->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	ground = new GameObject({ 15,30.f,-115 }, { -20.f,0.f,0.f }, { 10,4,10 }, "cube.obj", "rock.png", "ground", lvl1->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	ground = new GameObject({ 15,50.f,-130 }, { 20.f,0.f,0.f }, { 10,4,10 }, "cube.obj", "rock.png", "ground", lvl1->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	ground = new GameObject({ 15,70.f,-115 }, { -20.f,0.f,0.f }, { 10,4,10 }, "cube.obj", "rock.png", "ground", lvl1->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	ground = new GameObject({ 21,40.f,-122.5 }, { 0.f,0.f,0.f }, { 2,70,30 }, "cube.obj", "rock.png", "ground", lvl1->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	ground = new GameObject({ 36.5f,70.f,-122.5 }, { 0.f,0.f,0.f }, { 30,10,30 }, "cube.obj", "rock.png", "ground", lvl1->transform, GL_CLAMP_TO_BORDER);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	return lvl1;
}

GameObject* Application::InitLevel2()
{
	GameObject* lvl2 = new GameObject(nullptr, "lvl2");
	lvl2->enable = false;

	GameObject* ground = new GameObject({ 70.f,75.f,-122.5f }, { 0.f,0.f,0.f }, { 20,4,10 }, "cube.obj", "eridium.png", "ground", lvl2->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	ground = new GameObject({ 85.f,80.f,-122.5f }, { 0.f,0.f,0.f }, { 2,50,10 }, "cube.obj", "eridium.png", "ground", lvl2->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	ground = new GameObject({ 100.f,75.f,-122.5f }, { 0.f,0.f,0.f }, { 20,4,10 }, "cube.obj", "eridium.png", "ground", lvl2->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	ground = new GameObject({ 115.f,80.f,-122.5f }, { 0.f,0.f,0.f }, { 2,50,10 }, "cube.obj", "eridium.png", "ground", lvl2->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	ground = new GameObject({ 130.f,75.f,-122.5f }, { 0.f,0.f,20.f }, { 20,4,10 }, "cube.obj", "eridium.png", "ground", lvl2->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	ground = new GameObject({ 145.f,80.f,-122.5f }, { 0.f,0.f,0.f }, { 2,50,10 }, "cube.obj", "eridium.png", "ground", lvl2->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	ground = new GameObject({ 160.f,75.f,-122.5f }, { 0.f,0.f,-20.f }, { 20,4,10 }, "cube.obj", "eridium.png", "ground", lvl2->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	ground = new GameObject({ 176.f,80.f,-122.5f }, { 0.f,0.f,0.f }, { 5,50,10 }, "cube.obj", "eridium.png", "ground", lvl2->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	ground = new GameObject({ 195.f,77.f,-122.5f }, { 0.f,0.f,-20.f }, { 20,4,10 }, "cube.obj", "eridium.png", "ground", lvl2->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	ground = new GameObject({ 220.f,70.f,-122.5f }, { 0.f,0.f,0.f }, { 20,4,20 }, "cube.obj", "eridium.png", "ground", lvl2->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	return lvl2;
}

GameObject* Application::InitEndLevel()
{
	GameObject* end = new GameObject(nullptr, "end");
	end->enable = false;

	GameObject* ground = new GameObject({ 228.f,80.f + 2.f,-114.5f }, { 0.f,0.f,0.f }, { 4,20,4 }, "cube.obj", "eridium.png", "ground", end->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	ground = new GameObject({ 228.f,80.f + 2.f,-130.5f }, { 0.f,0.f,0.f }, { 4,20,4 }, "cube.obj", "eridium.png", "ground", end->transform);
	ground->AddComponent(AddCollider(Colliders::CUBE, ground));

	return end;
}

void Application::SwitchView()
{
	Camera* tempCam = currentCam;
	currentCam = oldCam;
	oldCam = tempCam;

	if (state == MenuState::PLAYING)
		state = MenuState::PAUSE;
	else
		state = MenuState::PLAYING;
}