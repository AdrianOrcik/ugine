#include "sandbox2D.h"
#include "imgui/imgui.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>


Ugine::Entity* square;

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), cameraController_(1280.0f / 720.0f, false, false, false)
{

}

Sandbox2D::~Sandbox2D()
{
	Ugine::ECS::DestroyEntities();
}

void Sandbox2D::OnAttach()
{
	// init random generation seed
	srand(time(NULL));

	// Camera settings
	// ------------
	cameraController_.SetCameraPosition({0.0f, 0.0f, 0.0f });
	cameraController_.SetZoomLevel(1.0f);
	

	square = Ugine::ECS::CreateEntity("Square");
	ECS_ADD_COMPONENT(square, Ugine::TransformComponent)
	ECS_ADD_COMPONENT(square, Ugine::RendererComponent)

	auto transform = ECS_GET_COMPONENT(square, Ugine::TransformComponent)
	auto renderer = ECS_GET_COMPONENT(square,Ugine::RendererComponent)

	renderer->SetCamera(&cameraController_.GetCamera());
	renderer->SetColor(Ugine::Color::White());
	square->SetActive(true);

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
		if (ImGui::Button("Test")) 
		{

		}
	ImGui::End();
}

void Sandbox2D::OnEvent(Ugine::Event & e)
{
	cameraController_.OnEvent(e);
}


