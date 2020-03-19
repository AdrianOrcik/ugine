#ifndef IMGUI_IMGUI_LAYOUT
#define IMGUI_IMGUI_LAYOUT

#include "ugine/layer.h"

#include "ugine/events/application_event.h"
#include "ugine/events/event.h"
#include "ugine/events/key_event.h"
#include "ugine/events/mouse_event.h"

namespace Ugine
{
	class UE_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();

	private:
		float mTime_ = 0.0f;
	};
}
#endif // !IMGUI_IMGGUI_LAYOUT
