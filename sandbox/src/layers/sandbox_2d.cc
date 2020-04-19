#include "sandbox_2d.h"
#include "imgui/imgui.h"

#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

#include "../scripts/sorting_manager.h"

//todo: root assets structure copy to bin build folder during building process
//		or somehow make references

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), cameraController_(1280.0f / 720.0f)
{

}

void Sandbox2D::OnAttach()
{
	//ECS implementation

	// sorting manager
	Ugine::Entity* manager =
		Ugine::ECS::CreateEntity("SortingManager");
	SortingManager* sortingManager = (SortingManager*)manager->AddComponent<SortingManager>();
	sortingManager->Elemets = elements_;

	// gameobjects
	// ------------
	for(int i = 0; i < 3; i++)
	{
		Ugine::Entity* GO = Ugine::ECS::CreateEntity("GameObject_" + std::to_string(i));
	
		Ugine::TransformComponent* transform =
			(Ugine::TransformComponent*)GO->AddComponent<Ugine::TransformComponent>();
		transform->SetPosition(glm::vec2(i, 0));
		transform->SetScale(glm::vec2(0.05f, ((float)i / 10.0f) + 0.1f));
		elements_.push_back(transform);

		Ugine::RendererComponent* renderer =
			(Ugine::RendererComponent*)GO->AddComponent<Ugine::RendererComponent>();
		renderer->SetCamera(&cameraController_.GetCamera());
	}
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

	// entities Update
	Ugine::ECS::Update(ts);
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(squareColor_));
	ImGui::End();
}

void Sandbox2D::OnEvent(Ugine::Event & e)
{
	cameraController_.OnEvent(e);
}
