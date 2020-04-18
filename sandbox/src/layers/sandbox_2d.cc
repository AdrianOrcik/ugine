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
	Ugine::Entity* gameObject = Ugine::ECS::CreateEntity("GameObject");
	Ugine::TransformComponent* transform = (Ugine::TransformComponent*)gameObject->AddComponent<Ugine::TransformComponent>();
	transform->SetPosition(glm::vec2(1.0f, 0.0f));
	transform->SetScale(glm::vec2(0.5f, 0.5f));
	Ugine::RendererComponent* renderer = (Ugine::RendererComponent*)gameObject->AddComponent<Ugine::RendererComponent>();
	renderer->SetColor({ 0.0f,0.0f,1.0f,1.0f });
	renderer->SetCamera(&cameraController_.GetCamera());

	Ugine::Entity* gameManager = Ugine::ECS::CreateEntity("GameManager");
	Ugine::TransformComponent* t = (Ugine::TransformComponent*)gameManager->AddComponent<Ugine::TransformComponent>();
	t->SetPosition(glm::vec2(-1.0f, 0.0f));
	t->SetScale(glm::vec2(0.5f, 0.5f));
	Ugine::RendererComponent* r = (Ugine::RendererComponent*)gameManager->AddComponent<Ugine::RendererComponent>();
	r->SetColor({ 1.0f,0.0f,1.0f,1.0f });
	r->SetCamera(&cameraController_.GetCamera());
	
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
	Ugine::Renderer2D::EndScene();
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
