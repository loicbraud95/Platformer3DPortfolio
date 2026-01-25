#include "SceneGraph.h"

SceneGraph* SceneGraph::instance = nullptr;

void SceneGraph::FixedUpdate()
{
	root->FixedUpdate();
}

void SceneGraph::Update()
{
	//debug container
	int sizemax = 100;
	if (root->GetChildren()[0]->GetChildren().size() > sizemax)
	{
		for (size_t i = 0; i < root->GetChildren()[0]->GetChildren().size(); i++)
		{
			if (root->GetChildren()[0]->GetChildren().size() <= sizemax)
				break;
			root->GetChildren()[0]->GetChildren()[0]->Delete();
			--i;
		}
	}
	//////////

	root->Update();
}

void SceneGraph::LateUpdate()
{
	root->LateUpdate();
}

void SceneGraph::Render()
{
	root->Render();
}

SceneGraph::SceneGraph()
{
	root = new Transform(true);
}

SceneGraph& SceneGraph::Get()
{
	if (instance == nullptr)
		instance = new SceneGraph();
	return *instance;
}

void SceneGraph::Destroy()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

SceneGraph::~SceneGraph()
{
	root->Delete();
}