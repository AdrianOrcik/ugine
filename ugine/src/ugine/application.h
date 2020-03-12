#ifndef UE_APPLICATION
#define UE_APPLICATION

#include "core.h"
#include "events/event.h"

#include "window.h"
#include "ugine/events/application_event.h"
#include "ugine/layer.h"
#include "ugine/layer_stack.h"

namespace Ugine {
	class UE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:

		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> window_;
		bool isRunning_ = true;
		LayerStack layerStack_;
	};

	// used by client sandbox
	// declaration of function, entry_point.h mark as external
	Application* CreateApplication();
}

#endif // !UE_APPLICATION
