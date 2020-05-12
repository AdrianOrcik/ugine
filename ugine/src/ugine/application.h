#pragma once

#include "core.h"
#include "events/event.h"

#include "window.h"
#include "ugine/events/application_event.h"
#include "ugine/layer.h"
#include "ugine/layer_stack.h"

#include "ugine/renderer/shader.h"
#include "ugine/renderer/buffer.h"
#include "ugine/renderer/vertex_array.h"

#include "ugine/imgui/imgui_layer.h"

#include "ugine/core/timestep.h"

//todo: this
//#include "ugine/imgui/imgui_layer.h"

namespace Ugine 
{

	class UE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
		
		inline bool IsRunning() { return isRunning_; }

		inline Window& GetWindow() { return *window_; }
		inline static Application& Get() { return *sInstance_; }
	private:

		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
		void AppPoolInput();

		std::unique_ptr<Window> window_;
		ImGuiLayer* imGuiLayer_;
		bool isRunning_ = true;
		bool isMinimized_ = false;
		LayerStack layerStack_;
		float lastFrameTime_ = 0.0f;
		static Application* sInstance_;
	};

	// used by client sandbox
	// declaration of function, entry_point.h mark as external
	Application* CreateApplication();
}

