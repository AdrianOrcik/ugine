#include "sandbox2D.h"
#include "imgui/imgui.h"

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

// Texture TOOD:
// 1. Texture is override other white textures
// 2. Draw texture is draw even if is not binding texture there 

Ugine::Entity* textureEntity;
Ugine::Entity* squareEntity;
Ugine::Ref<Ugine::Texture2D> texture;

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

	texture = Ugine::Texture2D::Create("assets/textures/container.jpg");
	
	textureEntity = Ugine::ECS::CreateEntity("TextureObj");
	ECS_ADD_COMPONENT(textureEntity, Ugine::TransformComponent)
	ECS_ADD_COMPONENT(textureEntity, Ugine::RendererComponent)

	auto transformTextureEntity = ECS_GET_COMPONENT(textureEntity, Ugine::TransformComponent)
	auto rendererTextureEntity = ECS_GET_COMPONENT(textureEntity,Ugine::RendererComponent)

	rendererTextureEntity->SetCamera(&cameraController_.GetCamera());
	rendererTextureEntity->SetColor(Ugine::Color::Red());
	//rendererTextureEntity->SetTexture(texture);
	textureEntity->SetActive(true);

	squareEntity = Ugine::ECS::CreateEntity("SquareObj");
	ECS_ADD_COMPONENT(squareEntity, Ugine::TransformComponent)
	ECS_ADD_COMPONENT(squareEntity, Ugine::RendererComponent)

	auto transformSquareEntity = ECS_GET_COMPONENT(squareEntity, Ugine::TransformComponent)
	auto rendererSquareEntity = ECS_GET_COMPONENT(squareEntity, Ugine::RendererComponent)

	transformSquareEntity->SetLocalPosition({ 1.0, 0.0 });
	rendererSquareEntity->SetCamera(&cameraController_.GetCamera());
	rendererSquareEntity->SetColor(Ugine::Color::Red());
	rendererSquareEntity->SetTexture(texture);
	squareEntity->SetActive(true);

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


