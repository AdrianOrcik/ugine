#pragma once

#include "event.h"

namespace Ugine
{

	class UE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			:mouseX_(x), mouseY_(y) {}

		inline float GetX() { return mouseX_; }
		inline float GetY() { return mouseY_; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << mouseX_ << ", " << mouseY_;
			return ss.str();
		}
		
		EVENT_CLASS_TYPE(MOUSE_MOVE);
		EVENT_CLASS_CATEGORY(MOUSE | INPUT);

	private:
		float mouseX_, mouseY_;
	};

	class UE_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			:xOffset_(xOffset), yOffset_(yOffset) {}

		inline float GetXOffset() const { return xOffset_; }
		inline float GetYOffset() const { return yOffset_; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		EVENT_CLASS_TYPE(MOUSE_SCROLL);
		EVENT_CLASS_CATEGORY(MOUSE | INPUT);

	private:
		float xOffset_, yOffset_;
	};

	class UE_API MouseButtonEvent : public Event
	{
	public:
		inline int GetMouseButton() const { return button_; }

		EVENT_CLASS_CATEGORY(MOUSE | INPUT);
	protected:
		MouseButtonEvent(int button)
			: button_(button) {}

		int button_;
	};

	class UE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << button_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MOUSE_BUTTON_PRESS);
	};

	class UE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int button)
			: MouseButtonEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << button_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MOUSE_BUTTON_RELEASE);
	};

}
