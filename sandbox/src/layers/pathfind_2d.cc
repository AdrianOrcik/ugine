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
bool startNode = false;
bool finalNode = false;
void Pathfind_2d::GridGenerator()
{
	//NOTE: grid 35x20
	//NOTE: [0,0] right bottom
	/*int index = 1;
	for (int i = 0; i < gridX_; i++)
	{
		for (int j = 0; j < gridY_; j++)
		{
			NodeElement* node = 
				NodeGenerator(index++, glm::vec2((float)((i - (gridX_ / 2.0f))), (float)((j - (gridY_ / 2.0f)))));
			grid_[i][j] = *node;
		}
	}*/

	//grid_[2][1].owner->SetActive(false);

	//grid_[0][1].IsWall = true;
	//Ugine::RendererComponent* r = 
	//	(Ugine::RendererComponent*)grid_[0][1].owner->GetComponent<Ugine::RendererComponent>();
	//r->SetColor(Ugine::Color::Red());

	//grid_[1][1].IsWall = true;
	//r =	(Ugine::RendererComponent*)grid_[1][1].owner->GetComponent<Ugine::RendererComponent>();
	//r->SetColor(Ugine::Color::Red());


	int index = 0;
	for (int row = 0; row < rowSize_; row++)
	{
		std::vector<NodeElement*> currentRow;
		for (int col = 0; col < colSize_; col++)
		{
			currentRow.push_back(NodeGenerator(index, glm::vec2(col,row)));
			index++;
		}

		grid_.push_back(currentRow);
	}





	/*
	7 8 9
	4 5 6
	1 2 3
	*/

	//grid_[0][0]->owner->SetActive(false);
	//grid_[0][4]->owner->SetActive(false);

	//grid_[4][4]->owner->SetActive(false);
	//grid_[4][0]->owner->SetActive(false);

	//auto startNode = (Ugine::RendererComponent*)grid_[15][10]->owner->GetComponent<Ugine::RendererComponent>();
	//startNode->SetColor(Ugine::Color::Yellow());

	//auto finalNode = (Ugine::RendererComponent*)grid_[4][4]->owner->GetComponent<Ugine::RendererComponent>();
	//finalNode->SetColor(Ugine::Color::Purple());

	//for (int i = 5; i < 20; i++)
	//{
	//	grid_[8][i]->IsWall = true;
	//	auto wall = (Ugine::RendererComponent*)grid_[8][i]->owner->GetComponent<Ugine::RendererComponent>();
	//	wall->SetColor(Ugine::Color::Red());
	//}

}

int offset = 0;
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

	//TODO: wall, regular, final, start 
	
	NodeElement* element =
		(NodeElement*)node->AddComponent<NodeElement>(position.x, position.y, index);

	int number = rand() % 4 + 1;
	offset++;
	switch (number)
	{
	case 1:
		//regular
		break;
	case 2:
		//wall
		break;
	case 3:
		if (!startNode)
		{
			startNode = true;
			startNode_ = element;
		}
		else number = 1;
		break;
	case 4:
		if (!finalNode && offset > 100)
		{
			finalNode = true;
			finalNode_ = element;
		}
		else number = 1;
		break;
	default:
		break;
	}

	element->SetType(number);

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
		//pfManager->Sorting(grid_, gridX_, gridY_);
		pfManager->Sorting(grid_,startNode_, finalNode_);
	}
	ImGui::End();
}

void Pathfind_2d::OnEvent(Ugine::Event & e)
{
	cameraController_.OnEvent(e);
}

