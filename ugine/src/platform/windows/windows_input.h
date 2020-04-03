#pragma once

#include "ugine/input/input.h"

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
		virtual bool IsExitButtonPressedImpl() override;
	};

}
