#include "uepch.h"

#include "application.h"
#include "log.h"

#include <GLFW/glfw3.h>

namespace Ugine {
	// todo: check std::bind function
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		window_ = std::unique_ptr<Window>(Window::Create());
		window_->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{
	
	}
	
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		CORE_LOG_TRACE("{0}", e);
	}

	void Application::Run()
	{
		while (isRunning_)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			window_->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		isRunning_ = false;
		return true;
	}

}