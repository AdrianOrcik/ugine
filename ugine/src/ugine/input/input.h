#pragma once

#include "ugine/core.h"
#include <iostream>
#include <utility>

namespace Ugine
{

	/// Input API provide directly acces on processes into system for user
	class UE_API Input
	{
	public:
		inline static bool IsKeyPressed(int keyCode) { return sInstance_->IsKeyPressedImpl(keyCode); }
		inline static bool IsMouseButtonPressed(int button) { return sInstance_->IsMouseButtonPressedImpl(button); }
		inline static bool IsExitButtonPressed() { return sInstance_->IsExitButtonPressedImpl(); }
		inline static std::pair<float, float> GetMousePosition() {return sInstance_->GetMousePositionImpl(); }
		inline static float GetMouseX() { return sInstance_->GetMouseXImpl(); }
		inline static float GetMouseY() { return sInstance_->GetMouseYImpl(); }

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual bool IsExitButtonPressedImpl() = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* sInstance_;
	};

}
