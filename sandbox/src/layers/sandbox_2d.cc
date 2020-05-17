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
	:Layer("Sandbox2D"), cameraController_(1280.0f / 720.0f)
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

	pooler = new Ugine::ObjectPooler();
	pooler->CreatePool("entities", *prefab, 20);

	// gameobjects
	// ------------
	cameraController_.SetCameraPosition({ 0.0f, 1.0f,0.0f });
	cameraController_.SetZoomLevel(1.0f);
	GeneratePooledObjects();

	LOG_INFO("gameObjects_ Count: {0}", gameObjects_.size());
	LOG_INFO("elements_ Count: {0}", elements_.size());
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Ugine::Timestep ts)
{
	LOG_INFO("CameraY: {0}", cameraController_.GetCameraPosition().y);
	LOG_INFO("ZoomLevel: {0}", cameraController_.GetZoomLevel());

	// camera update
	cameraController_.OnUpdate(ts);

	// render
	Ugine::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1 });
	Ugine::RenderCommand::Clear();
}

int index = 0;
void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Generation panel");
	if(true)
	{
		int tmpCount = elementCount_;
		ImGui::SliderInt("Count", &elementCount_, 4, 20);
		if (tmpCount != elementCount_)
		{
			if (elementCount_ <= 10)
			{
				cameraController_.SetCameraPosition({ 0.0f, 1.0f,0.0f });
				cameraController_.SetZoomLevel(1.0f);
			}
			else if (elementCount_ <= 15)
			{
				cameraController_.SetCameraPosition({ 0.0f, 1.5f,0.0f });
				cameraController_.SetZoomLevel(1.5f);
			}
			else if (elementCount_ <= 20)
			{
				cameraController_.SetCameraPosition({ 0.0f, 2.0f,0.0f });
				cameraController_.SetZoomLevel(2.0f);
			}

			GeneratePooledObjects();
		}

		if(ImGui::Button("Bubble Sort"))
		{
			sortingManager->SortBy(SortingManager::SortingType::Bubble);
		}

		if (ImGui::Button("Selection Sort"))
		{
			sortingManager->SortBy(SortingManager::SortingType::Selection);
		}
	}
	else 
	{
		if (ImGui::Button("Reset Simulation"))
		{
			Ugine::RoutineManager::DeleteRoutines();
			GeneratePooledObjects();
		}
	}
	ImGui::End();
}

void Sandbox2D::OnEvent(Ugine::Event & e)
{
	cameraController_.OnEvent(e);
}

void Sandbox2D::SetObject(Ugine::Entity* entity, int spawnPosition, int generatedValue)
{
	entity->SetActive(true);
	Ugine::TransformComponent* transform =
		(Ugine::TransformComponent*)entity->GetComponent<Ugine::TransformComponent>();
	transform->SetLocalPosition(glm::vec2((float)spawnPosition / 10.0f, 0.0f));
	transform->SetOffsetPosition(glm::vec2(0.0f, 0.0f));
	transform->SetScale(glm::vec2(0.05f, ((float)generatedValue / 10.0f)));

	Ugine::RendererComponent* renderer =
		(Ugine::RendererComponent*)entity->GetComponent<Ugine::RendererComponent>();
	renderer->SetColor(Ugine::Color::White());
	renderer->SetCamera(&cameraController_.GetCamera());

	SortingElement* element;
	if(entity->HasComponent<SortingElement>())
		entity->DestroyComponent<SortingElement>();

	element = (SortingElement*)entity->AddComponent<SortingElement>();
	element->Value = generatedValue;
	
	gameObjects_.push_back(entity);
	elements_.push_back(element);
}

void Sandbox2D::GeneratePooledObjects()
{
	//remove old game elements if exist
	for (auto gameObject : gameObjects_)
		gameObject->SetActive(false);

	gameObjects_.clear();
	elements_.clear();

	//generation of new vector of objects
	for (int i = 0; i < elementCount_; i++)
	{
		int generatedValue = rand() % elementCount_ * 2 + 1;
		//int spawnPosition = i - (elementCount_ / 2.0f);
		SetObject(pooler->GetPooledObj("entities"), i, generatedValue);
	}

	//update new elements for sort
	for (auto e : elements_)
	{
		if (!e->owner->IsActive())
			LOG_ERROR("Sandbox: DISABLED!");
	}

	sortingManager->SetElements(elements_);
}
