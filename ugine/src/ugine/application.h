#ifndef UE_APPLICATION
#define UE_APPLICATION

#include "core.h"
#include "events/event.h"
#include "window.h"
#include "ugine/events/application_event.h"

namespace Ugine {
	class UE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);
	private:

		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> window_;
		bool isRunning_ = true;
	};

	// used by client sandbox
	// declaration of function, entry_point.h mark as external
	Application* CreateApplication();
}

#endif // !UE_APPLICATION
