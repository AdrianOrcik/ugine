#include "sandbox_2d.h"
#include "imgui/imgui.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "../scripts/sorting_manager.h"
#include "../scripts/sorting_element.h"

//todo: root assets structure copy to bin build folder during building process
//		or somehow make references

SortingManager* sortingManager;
Ugine::Entity* manager;

// TODO: add pooler on low layer ?
Ugine::ObjectPooler* pooler;

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), cameraController_(1280.0f / 720.0f, false , false, false)
{

}

Sandbox2D::~Sandbox2D()
{
	Ugine::ECS::DestroyEntities();
	delete pooler;
}

Ugine::Entity* prefab;
void Sandbox2D::OnAttach()
{
	// init random generation seed
	srand(time(NULL));

	// sorting manager
	manager = Ugine::ECS::CreateEntity("SortingManager");
	sortingManager = (SortingManager*)manager->AddComponent<SortingManager>();
	manager->SetActive(true);

	prefab = Ugine::ECS::CreatePrefab("Object");
	prefab->AddComponent<Ugine::TransformComponent>();
	prefab->AddComponent<Ugine::RendererComponent>();
	//TODO: implement reflection -> engine will be able make prefab also from custom scripts
	//prefab->AddComponent<SortingElement>();

	//TODO: add prefab pooler into coroutine
	pooler = new Ugine::ObjectPooler();
	pooler->CreatePool("entities", *prefab, 60);

	// gameobjects
	// ------------
	cameraController_.SetCameraPosition({ -0.1f, 3.5f,0.0f });
	cameraController_.SetZoomLevel(3.25f);
	GeneratePooledElements();

}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Ugine::Timestep ts)
{
	// camera update
	cameraController_.OnUpdate(ts);

	// render
	Ugine::RenderCommand::SetClearColor(Ugine::Color::Background());
	Ugine::RenderCommand::Clear();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Generation panel");
	if(!sortingManager->IsRunning())
	{
		int tmpCount = elementCount_;
		ImGui::SliderInt("Count", &elementCount_, 4, 60);
		ImGui::SliderFloat("Speed", &speed_, 0.1f, 1.0f);
		Formulas::SetSortSpeed(speed_);

		if (tmpCount != elementCount_)
		{
			GeneratePooledElements();
		}
		
		if (ImGui::Button("Generate Elements"))
		{
			GeneratePooledElements();
		}

		if(ImGui::Button("Bubble Sort"))
		{
			sortingManager->SortBy(SortingManager::SortingType::Bubble);
		}

		if (ImGui::Button("Selection Sort"))
		{
			sortingManager->SortBy(SortingManager::SortingType::Selection);
		}

		if (ImGui::Button("Insertion Sort"))
		{
			sortingManager->SortBy(SortingManager::SortingType::Insertion);
		}

		if (ImGui::Button("Quick Sort"))
		{
			sortingManager->SortBy(SortingManager::SortingType::Quick);
		}

		if (ImGui::Button("Heap Sort"))
		{
			sortingManager->SortBy(SortingManager::SortingType::Heap);
		}

		if (ImGui::Button("Merge Sort"))
		{
			sortingManager->SortBy(SortingManager::SortingType::Merge);
		}
	}
	else 
	{
		if (ImGui::Button("Reset Simulation"))
		{
			Ugine::RoutineManager::DeleteRoutines();
			GeneratePooledElements();
			sortingManager->StopSimulation();
		}
	}
	ImGui::End();
}

void Sandbox2D::OnEvent(Ugine::Event & e)
{
	cameraController_.OnEvent(e);
}

void Sandbox2D::SetObject(Ugine::Entity* entity, int positionIndex, int generatedValue)
{
	entity->SetActive(true);

	Ugine::TransformComponent* transform =
		(Ugine::TransformComponent*)entity->GetComponent<Ugine::TransformComponent>();

	//NOTE: spawn scale computing
	float spawnScale = (1.0f / elementCount_) * 5.0f;

	//NOTE: position of elements in balance between - / + positions
	float spawnPosition = positionIndex - (elementCount_ / 2.0f);

	//NOTE: transform position into element unit
	spawnPosition /= 10.f;

	//NOTE: element padding computing
	spawnPosition += ((spawnScale * spawnPosition) * 10.0f);

	transform->SetLocalPosition(glm::vec2((float)spawnPosition, 0.0f));
	transform->SetOffsetPosition(glm::vec2(0.0f, 0.0f));

	transform->SetScale(glm::vec2(spawnScale, (float)generatedValue / 10.0f));

	Ugine::RendererComponent* renderer =
		(Ugine::RendererComponent*)entity->GetComponent<Ugine::RendererComponent>();
	renderer->SetColor(Ugine::Color::DefaultElement());
	renderer->SetCamera(&cameraController_.GetCamera());

	SortingElement* element;
	if(entity->HasComponent<SortingElement>())
		entity->DestroyComponent<SortingElement>();

	element = (SortingElement*)entity->AddComponent<SortingElement>();
	element->Value = generatedValue;
	
	gameObjects_.push_back(entity);
	elements_.push_back(element);
}

void Sandbox2D::GeneratePooledElements()
{
	//remove old game elements if exist
	for (auto gameObject : gameObjects_)
		gameObject->SetActive(false);

	gameObjects_.clear();
	elements_.clear();

	int arr[5] = { 4,10,3,5,1 };
	//generation of new vector of objects
	//elementCount_ = 5;
	for (int i = 0; i < elementCount_; i++)
	{
		int generatedValue = rand() % 50 + 10; // arr[i]
		SetObject(pooler->GetPooledObj("entities"), i, generatedValue);
	}

	sortingManager->SetElements(elements_);
}

