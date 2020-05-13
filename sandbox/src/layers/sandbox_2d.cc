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

//SortingManager* sortingManager;
//Ugine::Entity* manager;

// TODO: add pooler on low layer ?
Ugine::ObjectPooler* pooler;

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), cameraController_(1280.0f / 720.0f)
{

}

Sandbox2D::~Sandbox2D()
{
	delete pooler;
	//delete sortingManager;
	//delete manager;
}

Ugine::Entity* prefab;
void Sandbox2D::OnAttach()
{
	// init random generation seed
	srand(time(NULL));

	// sorting manager
	//manager = Ugine::ECS::CreateEntity("SortingManager");
	//sortingManager = (SortingManager*)manager->AddComponent<SortingManager>();

	// gameobjects
	// ------------
	//GenerateObjects();

	prefab = Ugine::ECS::CreatePrefab("Object");

	pooler = new Ugine::ObjectPooler();
	pooler->CreatePool("entities", *prefab, 3);

	LOG_INFO("Count: {0}", elements_.size());
}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Ugine::Timestep ts)
{
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
	ImGui::SliderInt("Count", &elementCount_, 1, 10);
	if (ImGui::Button("Generate"))
	{
		GenerateObjects();
	}
	if(ImGui::Button("Sort"))
	{

		Ugine::Entity* entity = pooler->GetPooledObj("entities");
		entity->Destroy();
		//sortingManager->SortBy();
	}

	ImGui::End();
}

void Sandbox2D::OnEvent(Ugine::Event & e)
{
	cameraController_.OnEvent(e);
}

void Sandbox2D::CreateObject(int index, int generatedValue)
{
	Ugine::Entity* GO = Ugine::ECS::CreateEntity("GameObject_" + std::to_string(index));
	gameObjects_.push_back(GO);

	Ugine::TransformComponent* transform =
		(Ugine::TransformComponent*)GO->AddComponent<Ugine::TransformComponent>();
	transform->SetLocalPosition(glm::vec2((float)index / 10.0f, 0));
	transform->SetOffsetPosition(glm::vec2(0,-0.5f));
	transform->SetScale(glm::vec2(0.05f, ((float)generatedValue / 10.0f)));

	Ugine::RendererComponent* renderer =
		(Ugine::RendererComponent*)GO->AddComponent<Ugine::RendererComponent>();
	renderer->SetCamera(&cameraController_.GetCamera());

	SortingElement* element =
		(SortingElement*)GO->AddComponent<SortingElement>();
	element->Value = generatedValue;
	elements_.push_back(element);
}

void Sandbox2D::GenerateObjects()
{
	////remove old game elements if exist
	//if(gameObjects_.size() > 0){
	//	for (auto gameObject : gameObjects_)
	//		gameObject->Destroy();
	//	
	//	gameObjects_.clear();
	//	elements_.clear();
	//}

	//generation of new vector of objects
	//for (int i = 0; i < elementCount_; i++)
	//{
	//	int generatedValue = rand() % elementCount_ * 2 + 1;
	//	CreateObject(i, generatedValue);
	//}

	//update new elements for sort
	//sortingManager->SetElements(elements_);
}
