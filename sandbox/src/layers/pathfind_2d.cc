#include "pathfind_2d.h"
#include "imgui/imgui.h"

#include "../pathfinding_scripts/pathfinding_manager.h"


PathfindingManager* pfManager;

Ugine::Entity* prefab;
Ugine::ObjectPooler* pooler;

Pathfind_2d::Pathfind_2d()
	:Layer("Pathfind"), cameraController_(1280.0f / 720.0f, true, true, true)
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

	prefab = Ugine::ECS::CreatePrefab("Node");
	prefab->AddComponent<Ugine::TransformComponent>();
	prefab->AddComponent<Ugine::RendererComponent>();

	pooler = new Ugine::ObjectPooler();
	pooler->CreatePool("Grid", *prefab, 1000);

	GridGenerator();
}

void Pathfind_2d::GridGenerator()
{
	//NOTE: grid 35x20
	//NOTE: [0,0] right bottom
	int index = 1;
	for (int i = 0; i < gridX_; i++)
	{
		for (int j = 0; j < gridY_; j++)
		{
			NodeElement* node = 
				NodeGenerator(index++, glm::vec2((float)((i - (gridX_ / 2.0f))), (float)((j - (gridY_ / 2.0f)))));
			grid_[i][j] = *node;
		}
	}

	//grid_[2][1].owner->SetActive(false);

	//grid_[0][1].IsWall = true;
	//Ugine::RendererComponent* r = 
	//	(Ugine::RendererComponent*)grid_[0][1].owner->GetComponent<Ugine::RendererComponent>();
	//r->SetColor(Ugine::Color::Red());

	//grid_[1][1].IsWall = true;
	//r =	(Ugine::RendererComponent*)grid_[1][1].owner->GetComponent<Ugine::RendererComponent>();
	//r->SetColor(Ugine::Color::Red());
}

NodeElement* Pathfind_2d::NodeGenerator(int index, glm::vec2 position)
{
	Ugine::Entity* node = pooler->GetPooledObj("Grid");

	Ugine::TransformComponent* transform =
		(Ugine::TransformComponent*)node->GetComponent<Ugine::TransformComponent>();
	transform->SetLocalPosition(position);
	transform->SetScale(glm::vec2(0.9f, 0.9f));

	Ugine::RendererComponent* renderer =
		(Ugine::RendererComponent*)node->GetComponent<Ugine::RendererComponent>();
	renderer->SetColor(Ugine::Color::White());
	renderer->SetCamera(&cameraController_.GetCamera());

	if (node->HasComponent<NodeElement>())
		node->DestroyComponent<NodeElement>();

	NodeElement* element =
		(NodeElement*)node->AddComponent<NodeElement>();
	element->Value = index;

	node->SetActive(true);
	return element;
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
		pfManager->Find(grid_, gridX_, gridY_);
	}
	ImGui::End();
}

void Pathfind_2d::OnEvent(Ugine::Event & e)
{
	cameraController_.OnEvent(e);
}

