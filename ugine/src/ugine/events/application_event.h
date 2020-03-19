#pragma once

#include "event.h"

namespace Ugine
{
	class UE_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			:width_(width), height_(height) {}

		inline unsigned int GetWidth() const { return width_; }
		inline unsigned int GetHeight() const { return height_; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << width_ << ", " << height_;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WINDOW_RESIZE);
		EVENT_CLASS_CATEGORY(APPLICATION);

	private:
		unsigned int width_, height_;
	};

	class UE_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WINDOW_CLOSE);
		EVENT_CLASS_CATEGORY(APPLICATION);
	};

	class UE_API AppTickEvent : public Event
	{
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(APP_TICK);
		EVENT_CLASS_CATEGORY(APPLICATION);
	};

	class UE_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(APP_UPDATE);
		EVENT_CLASS_CATEGORY(APPLICATION);
	};

	class UE_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}

		EVENT_CLASS_TYPE(APP_RENDER);
		EVENT_CLASS_CATEGORY(APPLICATION)
	};

}
