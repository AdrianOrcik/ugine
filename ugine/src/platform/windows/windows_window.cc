#include "uepch.h"

#include "windows_window.h"
#include "ugine/log.h"
#include "ugine/core.h"

namespace Ugine
{
	static bool sGLFWInitialized = false;

	Window* Window::Create(const WindowProperties& properties)
	{
		return new WindowsWindow(properties);
	}

	WindowsWindow::WindowsWindow(const WindowProperties& properties)
	{
		Init(properties);
	}
	
	WindowsWindow::~WindowsWindow()
	{
		ShutDown();
	}

	void WindowsWindow::Init(const WindowProperties& properties)
	{
		data_.title = properties.title;
		data_.width = properties.width;
		data_.height = properties.height;

		CORE_LOG_INFO("Creating window {0} ({1}, {2})", properties.title, properties.width, properties.height);

		if (!sGLFWInitialized)
		{
			// todo: glfwTerminate on system shutdown
			int success = glfwInit();
			UE_CORE_ASSERT(success, "GLFW is not Init!");

			sGLFWInitialized = true;
		}

		window_ = glfwCreateWindow((int)properties.width, (int)properties.height, data_.title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window_);
		glfwSetWindowUserPointer(window_, &data_);
		SetVSync(true);
	}

	void WindowsWindow::ShutDown()
	{
		glfwDestroyWindow(window_);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(window_);
	}

	void WindowsWindow::SetVSync(bool isEnabled)
	{
		// todo: check swap buffers
		if (isEnabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		data_.vSync = isEnabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return data_.vSync;
	}
}