#include "pathfind_2d.h"
#include "imgui/imgui.h"

Pathfind_2d::Pathfind_2d()
	:Layer("Pathfind"), cameraController_(1280.0f / 720.0f, true, false, false)
{
}

Pathfind_2d::~Pathfind_2d()
{
}

void Pathfind_2d::OnAttach()
{
	cameraController_.SetCameraPosition(glm::vec3(-0.5f, -0.4f, 0.0f));
	GridGenerator();
}

void Pathfind_2d::ClickTest()
{
	LOG_INFO("External Click");
}

void Pathfind_2d::GridGenerator()
{
	//int index = 0;
	//whole grid 35x20
	int gridX = 5;
	int gridY = 5;
	//for (int i = 0; i < gridX; i++)
	//{
	//	for (int j = 0; j < gridY; j++)
	//	{
	//		BoxGenerator(0, glm::vec2((float)((i - (gridX / 2.0f))), (float)((j - (gridY / 2.0f)))));
	//		//index++;
	//	}
	//}

	BoxGenerator(0, glm::vec2((float)(5), (float)(5)));
	//BoxGenerator(0, glm::vec2((float)(0.1f), (float)(0.1f)));
	//BoxGenerator(0, glm::vec2((float)(0 / 10.0f), (float)(1 / 10.0f)));
	//BoxGenerator(0, glm::vec2((float)(1 / 10.0f), (float)(1 / 10.0f)));
}

void Pathfind_2d::BoxGenerator(int index, glm::vec2 position)
{
	Ugine::Entity* box = Ugine::ECS::CreateEntity("Box_" + index);
	box->AddComponent<Ugine::TransformComponent>();
	box->AddComponent<Ugine::RendererComponent>();
	box->AddComponent<Ugine::ButtonComponent>();

	Ugine::TransformComponent* transform =
		(Ugine::TransformComponent*)box->GetComponent<Ugine::TransformComponent>();
	transform->SetLocalPosition(position);
	//transform->SetOffsetPosition(glm::vec2(0.0f, 0.0f));
	transform->SetScale(glm::vec2(0.9f, 0.9f));

	Ugine::RendererComponent* renderer =
		(Ugine::RendererComponent*)box->GetComponent<Ugine::RendererComponent>();
	renderer->SetColor(Ugine::Color::White());
	renderer->SetCamera(&cameraController_.GetCamera());

	Ugine::ButtonComponent* button =
		(Ugine::ButtonComponent*)box->GetComponent<Ugine::ButtonComponent>();
	button->OnClickCallback.push_back(std::bind(&Pathfind_2d::ClickTest, this));
	box->SetActive(true);
}


void Pathfind_2d::OnDetach()
{
}

void Pathfind_2d::OnUpdate(Ugine::Timestep ts)
{
	//LOG_INFO("[{0},{1}]", cameraController_.GetCameraPosition().x, cameraController_.GetCameraPosition().y);

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

