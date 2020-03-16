#ifndef IMGUI_IMGUI_LAYOUT
#define IMGUI_IMGUI_LAYOUT

#include "ugine/layer.h"

#include "ugine/events/application_event.h"
#include "ugine/events/event.h"
#include "ugine/events/key_event.h"
#include "ugine/events/mouse_event.h"

namespace Ugine
{
	extern "C" class UE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();
		void OnUpdate();
		void OnEvent(Event& e);
	
	private:
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
	
	private:
		float mTime_ = 0.0f;
	};
}
#endif // !IMGUI_IMGGUI_LAYOUT
