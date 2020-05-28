#include "pathfind_2d.h"
#include "imgui/imgui.h"

Pathfind_2d::Pathfind_2d()
	:Layer("Pathfind"), cameraController_(1280.0f / 720.0f, true, true, true)
{
}

Pathfind_2d::~Pathfind_2d()
{
}

Ugine::Entity* box;
Ugine::Entity* box2;
void Pathfind_2d::OnAttach()
{
	box = Ugine::ECS::CreateEntity("Box");
	box->AddComponent<Ugine::TransformComponent>();
	box->AddComponent<Ugine::RendererComponent>();
	box->AddComponent<Ugine::ButtonComponent>();

	Ugine::TransformComponent* transform = 
		(Ugine::TransformComponent*)box->GetComponent<Ugine::TransformComponent>();
	transform->SetLocalPosition(glm::vec2(0.0f, 0.0f));
	transform->SetOffsetPosition(glm::vec2(0.0f, 0.0f));
	transform->SetScale(glm::vec2(0.1f, 0.1f));

	Ugine::RendererComponent* renderer =
		(Ugine::RendererComponent*)box->GetComponent<Ugine::RendererComponent>();
	renderer->SetColor(Ugine::Color::White());
	renderer->SetCamera(&cameraController_.GetCamera());

	Ugine::ButtonComponent* button = 
		(Ugine::ButtonComponent*)box->GetComponent<Ugine::ButtonComponent>();
	button->OnClickCallback.push_back(std::bind(&Pathfind_2d::ClickTest, this));
	box->SetActive(true);

	box2 = Ugine::ECS::CreateEntity("Box2");
	box2->AddComponent<Ugine::TransformComponent>();
	box2->AddComponent<Ugine::RendererComponent>();
	box2->AddComponent<Ugine::ButtonComponent>();

	Ugine::TransformComponent* transform2 =
		(Ugine::TransformComponent*)box2->GetComponent<Ugine::TransformComponent>();
	transform2->SetLocalPosition(glm::vec2(1.0f, 0.0f));
	transform2->SetOffsetPosition(glm::vec2(0.0f, 0.0f));
	transform2->SetScale(glm::vec2(0.1f, 0.1f));

	Ugine::RendererComponent* renderer2 =
		(Ugine::RendererComponent*)box2->GetComponent<Ugine::RendererComponent>();
	renderer2->SetColor(Ugine::Color::White());
	renderer2->SetCamera(&cameraController_.GetCamera());

	Ugine::ButtonComponent* button2 =
		(Ugine::ButtonComponent*)box2->GetComponent<Ugine::ButtonComponent>();
	button2->OnClickCallback.push_back(std::bind(&Pathfind_2d::ClickTest, this));
	box2->SetActive(true);
}

void Pathfind_2d::ClickTest()
{
	LOG_INFO("External Click");
}


void Pathfind_2d::OnDetach()
{
}

void Pathfind_2d::OnUpdate(Ugine::Timestep ts)
{
	// camera update
	cameraController_.OnUpdate(ts);

	// render
	Ugine::RenderCommand::SetClearColor(Ugine::Color::Background());
	Ugine::RenderCommand::Clear();
}

void Pathfind_2d::OnImGuiRender()
{
	ImGui::Begin("Settings Panel");
	
	ImGui::End();
}

void Pathfind_2d::OnEvent(Ugine::Event & e)
{
	cameraController_.OnEvent(e);
}

