#include "uepch.h"
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
	}
	
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(windowHandle_);
	}
}