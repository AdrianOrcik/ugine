#pragma once

#include "core.h"
#include "events/event.h"

namespace Ugine
{
	struct WindowProperties
	{
		std::string title;
		unsigned int width;
		unsigned int height;

		WindowProperties(const std::string& title = "Ugine",
							unsigned int width = 1280,
							unsigned int height = 720)
			:title(title), width(width), height(height) {}
	};

	// interface for desktop windows based system 
	class UE_API Window
	{
	public:
		// todo: !check functions
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

		// window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool isEnabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProperties& properties = WindowProperties());
	};
}
