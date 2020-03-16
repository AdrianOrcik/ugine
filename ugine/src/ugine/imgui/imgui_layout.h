#ifndef IMGUI_IMGUI_LAYOUT
#define IMGUI_IMGUI_LAYOUT

#include "ugine/layer.h"

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
		float mTime_ = 0.0f;
	};
}
#endif // !IMGUI_IMGGUI_LAYOUT
