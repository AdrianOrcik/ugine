#ifndef WINDOWS_INPUT
#define WINDOWS_INPUT

#include "ugine/input.h"

namespace Ugine
{

	class WindowsInput : public Input
	{
		// Inherited via Input
		virtual bool IsKeyPressedImpl(int keycode) override;
		virtual bool IsMouseButtonPressedImpl(int button) override;
		virtual std::pair<float, float> GetMousePositionImpl() override;
		virtual float GetMouseXImpl() override;
		virtual float GetMouseYImpl() override;
	};

}

#endif // !WINDOWS_INPUT
