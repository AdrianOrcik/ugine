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
	//Ugine::Entity* gameObject = Ugine::ECS::CreateEntity("GameObject");
	//gameObject->AddComponent<Ugine::Transform>(5, 5);

	texture_ = Ugine::Texture2D::Create("assets/textures/container.jpg");

}

void Sandbox2D::OnDetach()
{

}

void Sandbox2D::OnUpdate(Ugine::Timestep ts)
{\
	// entities Update
	//Ugine::ECS::Update(ts);

	// camera update
	cameraController_.OnUpdate(ts);

	// render
	Ugine::RenderCommand::SetClearColor({ 0.1f,0.1f,0.1f,1 });
	Ugine::RenderCommand::Clear();

	Ugine::Renderer2D::BegineScene(cameraController_.GetCamera());
	Ugine::Renderer2D::DrawQuad({ -1.0f, 0.0f }, { 0.8f, 0.8f }, { 0.8f, 0.2f, 0.3f, 1.0f });
	Ugine::Renderer2D::DrawQuad({ 0.5f, -0.5f }, { 0.5f, 0.75f }, { 0.2f, 0.3f, 0.8f, 1.0f });
	Ugine::Renderer2D::DrawQuad({ 0.0f, 0.0f, -0.1f }, { 10.0f, 10.0f }, texture_);
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
