#include "uepch.h"

#include "application.h"

#include "events/application_event.h"
#include "log.h"

#include <GLFW/glfw3.h>

namespace Ugine {

	Application::Application()
	{
		window_ = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	
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

}