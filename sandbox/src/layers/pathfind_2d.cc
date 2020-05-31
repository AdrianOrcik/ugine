#include "pathfind_2d.h"
#include "imgui/imgui.h"

#include "../pf_scripts/pathfinding_manager.h"


PathfindingManager* pfManager;
Pathfind_2d::Pathfind_2d()
	:Layer("Pathfind"), cameraController_(1280.0f / 720.0f, false, false, false)
{

}

Pathfind_2d::~Pathfind_2d()
{

}

void Pathfind_2d::OnAttach()
{
	cameraController_.SetCameraPosition(glm::vec3(-0.5f, -0.4f, 0.0f));

	Ugine::Entity* pfEntity = Ugine::ECS::CreateEntity("PathfindingManager");
	pfManager = (PathfindingManager*)pfEntity->AddComponent<PathfindingManager>();
	pfEntity->SetActive(true);

	GridGenerator();
}

void Pathfind_2d::GridGenerator()
{
	//NOTE: grid 35x20
	//NOTE: [0,0] right bottom
	int gridX = 3;
	int gridY = 3;
	int index = 1;

	for (int i = 0; i < gridX; i++)
	{
		for (int j = 0; j < gridY; j++)
		{
			NodeElement* node = 
				BoxGenerator(index, glm::vec2((float)((i - (gridX / 2.0f))), (float)((j - (gridY / 2.0f)))));
			grid_[i][j] = *node;
			index++;
		}
	}

	grid_[0][1].IsWall = true;
	Ugine::RendererComponent* r = 
		(Ugine::RendererComponent*)grid_[0][1].owner->GetComponent<Ugine::RendererComponent>();
	r->SetColor(Ugine::Color::Red());

	grid_[1][1].IsWall = true;
	r =	(Ugine::RendererComponent*)grid_[1][1].owner->GetComponent<Ugine::RendererComponent>();
	r->SetColor(Ugine::Color::Red());
}

NodeElement* Pathfind_2d::BoxGenerator(int index, glm::vec2 position)
{
	Ugine::Entity* box = Ugine::ECS::CreateEntity("Box_" + index);
	box->AddComponent<Ugine::TransformComponent>();
	box->AddComponent<Ugine::RendererComponent>();
	box->AddComponent<NodeElement>();

	Ugine::TransformComponent* transform =
		(Ugine::TransformComponent*)box->GetComponent<Ugine::TransformComponent>();
	transform->SetLocalPosition(position);
	transform->SetScale(glm::vec2(0.9f, 0.9f));

	Ugine::RendererComponent* renderer =
		(Ugine::RendererComponent*)box->GetComponent<Ugine::RendererComponent>();
	renderer->SetColor(Ugine::Color::White());
	renderer->SetCamera(&cameraController_.GetCamera());

	NodeElement* node =
		(NodeElement*)box->GetComponent<NodeElement>();
	node->Value = index;

	box->SetActive(true);
	return node;
}

void Pathfind_2d::OnDetach()
{

}

void Pathfind_2d::OnUpdate(Ugine::Timestep ts)
{
	//LOG_INFO("[{0},{1}]", cameraController_.GetCameraPosition().x, cameraController_.GetCameraPosition().y);

	// camera update
	cameraController_.OnUpdate(ts);

	// render
	Ugine::RenderCommand::SetClearColor(Ugine::Color::Background());
	Ugine::RenderCommand::Clear();
}

void Pathfind_2d::OnImGuiRender()
{
	ImGui::Begin("Settings Panel");
	if (ImGui::Button("Find"))
	{
		pfManager->Find(grid_);
	}
	ImGui::End();
}

void Pathfind_2d::OnEvent(Ugine::Event & e)
{
	cameraController_.OnEvent(e);
}

