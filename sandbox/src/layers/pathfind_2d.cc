#include "pathfind_2d.h"
#include "imgui/imgui.h"

#include "../pathfinding_scripts/pathfinding_manager.h"

#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

PathfindingManager* pfManager;

Ugine::Entity* prefab;
Ugine::ObjectPooler* pooler;

Pathfind_2d::Pathfind_2d()
	:Layer("Pathfind"), cameraController_(1280.0f / 720.0f, true, true, true)
{
	srand(time(NULL));
}

Pathfind_2d::~Pathfind_2d()
{
	delete prefab;
	delete pooler;
	delete pfManager;
}

void Pathfind_2d::OnAttach()
{
	cameraController_.SetCameraPosition(glm::vec3(17.0f, 10.0f, 0.0f));
	cameraController_.SetZoomLevel(10.5f);

	Ugine::Entity* pfEntity = Ugine::ECS::CreateEntity("PathfindingManager");
	pfManager = (PathfindingManager*)pfEntity->AddComponent<PathfindingManager>();
	pfEntity->SetActive(true);

	prefab = Ugine::ECS::CreatePrefab("Node");
	prefab->AddComponent<Ugine::TransformComponent>();
	prefab->AddComponent<Ugine::RendererComponent>();

	pooler = new Ugine::ObjectPooler();
	pooler->CreatePool("Grid", *prefab, 1000);

	GenerateGrid();
}


void Pathfind_2d::OnDetach()
{

}

void Pathfind_2d::OnUpdate(Ugine::Timestep ts)
{
	//LOG_INFO("[{0},{1}]", cameraController_.GetCameraPosition().x, cameraController_.GetCameraPosition().y);
	//LOG_INFO("[{0}]", cameraController_.GetZoomLevel());
	
	// camera update
	cameraController_.OnUpdate(ts);

	// render
	Ugine::RenderCommand::SetClearColor(Ugine::Color::Background());
	Ugine::RenderCommand::Clear();
}

void Pathfind_2d::OnImGuiRender()
{
	ImGui::Begin("Settings Panel");

	if (ImGui::Button("Regenerate Grid"))
	{
		RegenerateGrid();
	}

	if (ImGui::Button("Run Dijkstra"))
	{
		pfManager->Sorting(grid_,startNode_, finalNode_);
	}

	ImGui::End();
}

void Pathfind_2d::OnEvent(Ugine::Event & e)
{
	cameraController_.OnEvent(e);
}

void Pathfind_2d::GenerateGrid()
{
	int index = 0;
	for (int row = 0; row < ROW_SIZE; row++)
	{
		std::vector<NodeElement*> currentRow;
		for (int col = 0; col < COL_SIZE; col++)
		{
			currentRow.push_back(CreateNode(index, glm::vec2(col, row)));
			index++;
		}

		grid_.push_back(currentRow);
	}

	GenerateStartEndNode();
}

void Pathfind_2d::RegenerateGrid()
{
	for (int row = 0; row < ROW_SIZE; row++)
	{
		for (int col = 0; col < COL_SIZE; col++)
		{
			NodeElement* node = grid_[row][col];
			node->SetType(NodeFlag::Regular);
			node->SetType(!IsWallNode(glm::vec2(col, row)) ? NodeFlag::Regular : NodeFlag::Wall);
		}
	}

	GenerateStartEndNode();
}

NodeElement* Pathfind_2d::CreateNode(int index, glm::vec2 position)
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
		(NodeElement*)node->AddComponent<NodeElement>(position.x, position.y, index);

	element->SetType(IsWallNode(position) ? NodeFlag::Wall : NodeFlag::Regular);

	node->SetActive(true);
	return element;
}

int Pathfind_2d::GetNodePosition(bool isEven, int end)
{
	while (1)
	{
		int num = rand() % end;
		if (isEven && num % 2 == 0)
			return num;
		if (!isEven && num % 2 != 0)
			return num;
	}
}

bool Pathfind_2d::IsWallNode(glm::vec2 position)
{
	bool isEvenRow = (int)position.y % 2 == 0 && (int)position.x % 2 == 0;
	bool isSecondRow = (int)position.x % 8 == 0;
	if (isSecondRow)
		isEvenRow = (int)position.y % 2 != 0;

	return isEvenRow;
}

void Pathfind_2d::GenerateStartEndNode()
{
	startNode_ = grid_[ROW_MIDDLE - 1][COL_MIDDLE - 1];
	startNode_->SetType(NodeFlag::Start);

	int r = GetNodePosition(true, ROW_SIZE);
	int c = GetNodePosition(false, COL_SIZE);
	
	if(finalNode_ !=nullptr)
		finalNode_->SetType(NodeFlag::Regular);

	finalNode_ = grid_[r][c];
	finalNode_->SetType(NodeFlag::Target);
}


