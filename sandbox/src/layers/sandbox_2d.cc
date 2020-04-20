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

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), cameraController_(1280.0f / 720.0f)
{

}

SortingManager* sortingManager;
Ugine::Entity* manager;
void Sandbox2D::OnAttach()
{
	// init random generation seed
	srand(time(NULL));

	// sorting manager
	manager =
		Ugine::ECS::CreateEntity("SortingManager");
	sortingManager = (SortingManager*)manager->AddComponent<SortingManager>();

	// gameobjects
	// ------------
	for(int i = 0; i < 5; i++)
	{
		int generatedValue = rand() % 5 + 1;
		//todo: add random regenerator

		Ugine::Entity* GO = Ugine::ECS::CreateEntity("GameObject_" + std::to_string(i));
	
		Ugine::TransformComponent* transform =
			(Ugine::TransformComponent*)GO->AddComponent<Ugine::TransformComponent>();
		transform->SetPosition(glm::vec2((float)i /10.0f, 0));
		transform->SetScale(glm::vec2(0.05f, ((float)generatedValue / 10.0f)));

		Ugine::RendererComponent* renderer =
			(Ugine::RendererComponent*)GO->AddComponent<Ugine::RendererComponent>();
		renderer->SetCamera(&cameraController_.GetCamera());

		SortingElement* element =
			(SortingElement*)GO->AddComponent<SortingElement>();
		element->Value = generatedValue;
		elements_.push_back(element);
	}

	LOG_INFO("Count: {0}", elements_.size());
	sortingManager->Elemets = elements_;
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

	// entities Update
	Ugine::ECS::Update(ts);
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor_));
	if(ImGui::Button("Sort"))
	{
		sortingManager->BubbleSort();
	}
	ImGui::End();
}

void Sandbox2D::OnEvent(Ugine::Event & e)
{
	cameraController_.OnEvent(e);
}
