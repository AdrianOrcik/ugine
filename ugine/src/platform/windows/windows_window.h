#pragma once

#include "ugine/window.h"
#include "ugine/renderer/graphic_context.h"

#include <GLFW/glfw3.h>

namespace Ugine
{
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& properties);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return data_.width; }
		inline unsigned int GetHeight() const override { return data_.height; }

		// window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { data_.EventCallback = callback; }
		void SetVSync(bool isEnabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return window_; }

	private:
		virtual void Init(const WindowProperties& properties);
		virtual void ShutDown();

		GLFWwindow* window_;
		GraphicContext* context_;

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			bool vSync;

			EventCallbackFn EventCallback;
		};

		WindowData data_;
	};
}
