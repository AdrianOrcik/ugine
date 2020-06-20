#include "sandbox2D.h"
#include "imgui/imgui.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

// Texture TOOD:
// 1. Texture is override other white textures
// 2. Draw texture is draw even if is not binding texture there 

Ugine::Entity* containerEntity;
Ugine::Entity* squareEntity;
Ugine::Entity* boxEntity;

Ugine::Ref<Ugine::Texture2D> container;
Ugine::Ref<Ugine::Texture2D> box;

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), cameraController_(1280.0f / 720.0f, true, false, false)
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

	//TODO: What is loaded later, this texture override everything
	box = Ugine::Texture2D::Create("assets/textures/box.jpg");
	container = Ugine::Texture2D::Create("assets/textures/container.jpg");

	// Texture - obj with container texture
	containerEntity = Ugine::ECS::CreateEntity("TextureObj");
	ECS_ADD_COMPONENT(containerEntity, Ugine::TransformComponent)
	ECS_ADD_COMPONENT(containerEntity, Ugine::RendererComponent)

	auto transformTextureEntity = ECS_GET_COMPONENT(containerEntity, Ugine::TransformComponent)
	auto rendererTextureEntity = ECS_GET_COMPONENT(containerEntity,Ugine::RendererComponent)

	rendererTextureEntity->SetCamera(&cameraController_.GetCamera());
	rendererTextureEntity->SetColor(Ugine::Color::Red());
	rendererTextureEntity->SetTexture(container);
	containerEntity->SetActive(true);


	// Square - obj with runtime generated white texture
	squareEntity = Ugine::ECS::CreateEntity("SquareObj");
	ECS_ADD_COMPONENT(squareEntity, Ugine::TransformComponent)
	ECS_ADD_COMPONENT(squareEntity, Ugine::RendererComponent)

	auto transformSquareEntity = ECS_GET_COMPONENT(squareEntity, Ugine::TransformComponent)
	auto rendererSquareEntity = ECS_GET_COMPONENT(squareEntity, Ugine::RendererComponent)

	transformSquareEntity->SetLocalPosition({ 1.0, 0.0 });
	rendererSquareEntity->SetCamera(&cameraController_.GetCamera());
	rendererSquareEntity->SetColor(Ugine::Color::Red());
	rendererSquareEntity->SetTexture(container);
	squareEntity->SetActive(true);


	// Square - obj with runtime generated white texture
	boxEntity = Ugine::ECS::CreateEntity("BoxObj");
	ECS_ADD_COMPONENT(boxEntity, Ugine::TransformComponent)
	ECS_ADD_COMPONENT(boxEntity, Ugine::RendererComponent)

	auto transformBoxEntity = ECS_GET_COMPONENT(boxEntity, Ugine::TransformComponent)
	auto rendererBoxEntity = ECS_GET_COMPONENT(boxEntity, Ugine::RendererComponent)

	transformBoxEntity->SetLocalPosition({ 2.0, 0.0 });
	rendererBoxEntity->SetCamera(&cameraController_.GetCamera());
	rendererBoxEntity->SetColor(Ugine::Color::Yellow());
	//rendererBoxEntity->SetTexture(container);
	boxEntity->SetActive(true);

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


