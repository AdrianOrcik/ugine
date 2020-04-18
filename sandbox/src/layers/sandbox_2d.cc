#include "sandbox_2d.h"
#include "imgui/imgui.h"

#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>

//todo: root assets structure copy to bin build folder during building process
//		or somehow make references

Sandbox2D::Sandbox2D()
	:Layer("Sandbox2D"), cameraController_(1280.0f / 720.0f)
{

}

void Sandbox2D::OnAttach()
{
	//ECS implementation

	// GameObject 1
	// ------------
	Ugine::Entity* GO_1 = Ugine::ECS::CreateEntity("GameObject_1");
	
	Ugine::TransformComponent* transform_GO_1 = 
		(Ugine::TransformComponent*)GO_1->AddComponent<Ugine::TransformComponent>();
	transform_GO_1->SetPosition(glm::vec2(1.0f, 0.0f));
	transform_GO_1->SetScale(glm::vec2(0.5f, 0.5f));
	
	Ugine::RendererComponent* renderer_GO_1 = 
		(Ugine::RendererComponent*)GO_1->AddComponent<Ugine::RendererComponent>();
	renderer_GO_1->SetColor({ 0.0f,0.0f,1.0f,1.0f });
	renderer_GO_1->SetCamera(&cameraController_.GetCamera());

	// GameObject 2
	// ------------
	Ugine::Entity* GO_2 = Ugine::ECS::CreateEntity("GameObject_2");

	Ugine::TransformComponent* transform_GO_2 =
		(Ugine::TransformComponent*)GO_2->AddComponent<Ugine::TransformComponent>();
	transform_GO_2->SetPosition(glm::vec2(-1.0f, 0.0f));
	transform_GO_2->SetScale(glm::vec2(0.5f, 0.5f));
	
	Ugine::RendererComponent* renderer_GO_2 =
		(Ugine::RendererComponent*)GO_2->AddComponent<Ugine::RendererComponent>();
	renderer_GO_2->SetColor({ 1.0f,0.0f,1.0f,1.0f });
	renderer_GO_2->SetCamera(&cameraController_.GetCamera());

	// GameObject 3
	// ------------
	Ugine::Entity* GO_3 = Ugine::ECS::CreateEntity("GameObject_3");

	Ugine::TransformComponent* transform_GO_3 =
		(Ugine::TransformComponent*)GO_3->AddComponent<Ugine::TransformComponent>();
	transform_GO_3->SetPosition(glm::vec2(0.0f, -0.5f));
	transform_GO_3->SetScale(glm::vec2(0.5f, 0.5f));
	
	Ugine::RendererComponent* renderer_GO_3 =
		(Ugine::RendererComponent*)GO_3->AddComponent<Ugine::RendererComponent>();
	renderer_GO_3->SetColor({ 0.0f,1.0f,1.0f,1.0f });
	renderer_GO_3->SetCamera(&cameraController_.GetCamera());
	
	//box_ = Ugine::Texture2D::Create("assets/textures/box.jpg");
	//container_ = Ugine::Texture2D::Create("assets/textures/container.jpg");
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

	//Ugine::Renderer2D::BegineScene(cameraController_.GetCamera());
	//Ugine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	//Ugine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	////Ugine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, container_);
	Ugine::Renderer2D::OnEnd();
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
