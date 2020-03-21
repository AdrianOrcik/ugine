#include "uepch.h"

#include "ugine/log.h"
#include "opengl_context.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <gl/GL.h>

namespace Ugine
{
	OpenGLContext::OpenGLContext(GLFWwindow * windowHandle)
		:windowHandle_(windowHandle)
	{
		UE_CORE_ASSERT(windowHandle, "Window handle is null")
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(windowHandle_);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		UE_CORE_ASSERT(status, "Glad is null!")

		CORE_LOG_INFO("OpenGL Info:");
		CORE_LOG_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		CORE_LOG_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		CORE_LOG_INFO("  Version: {0}", glGetString(GL_VERSION));
	}
	
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(windowHandle_);
	}
}