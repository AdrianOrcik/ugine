#pragma once

#include "ugine/core.h"
#include "ugine/renderer/graphic_context.h"

struct GLFWwindow;

namespace Ugine
{

	class OpenGLContext : public GraphicContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;

	private:
		GLFWwindow* windowHandle_;
	};

}