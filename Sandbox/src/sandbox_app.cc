#include <ugine.h>

class ExampleLayer : public Ugine::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
	}

	void OnUpdate() override
	{
		LOG_INFO("ExampleLayer::Update");
	}

	void OnEvent(Ugine::Event& event) override
	{
		LOG_INFO("{0}", event);
	}
};


class Sandbox : public Ugine::Application
{
public:
	Sandbox()
	{	
		PushLayer(new ExampleLayer());
		PushOverlay(new Ugine::ImGuiLayer());
	}

	~Sandbox()
	{
		
	}
};

// called by ugine\entry_point.h
Ugine::Application* Ugine::CreateApplication() 
{
	LOG_TRACE("Sandbox Created!");
	return new Sandbox();
}