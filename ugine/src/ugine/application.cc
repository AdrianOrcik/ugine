#include "uepch.h"

#include "application.h"
#include "log.h"

#include <glad/glad.h>

#include "input.h"

namespace Ugine {
	// todo: !check std::bind function
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::sInstance_ = nullptr;

	Application::Application()
	{
		UE_CORE_ASSERT(!sInstance_, "Application already exist!");
		sInstance_ = this;

		window_ = std::unique_ptr<Window>(Window::Create());
		window_->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
		delete &layerStack_;
		delete &window_;
	}

	void Application::PushLayer(Layer* layer)
	{
		layerStack_.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		layerStack_.PushOverlay(layer);
		layer->OnAttach();
	}
	
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		CORE_LOG_TRACE("{0}", e);

		for (auto it = layerStack_.end(); it != layerStack_.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (isRunning_)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : layerStack_)
				layer->OnUpdate();

			auto[x, y] = Input::GetMousePosition();
			CORE_LOG_TRACE("{0},{1}", x,y);

			window_->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		isRunning_ = false;
		return true;
	}

}