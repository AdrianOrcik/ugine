#include "uepch.h"

#include "application.h"

#include "events/application_event.h"
#include "log.h"

namespace Ugine {

	Application::Application()
	{

	}

	Application::~Application()
	{
	
	}

	void Application::Run()
	{
		WindowResizeEvent e(800, 600);
		if (e.IsInCategory(APPLICATION)) {
			CORE_LOG_TRACE(e);
		}

		while (true);
	}

}