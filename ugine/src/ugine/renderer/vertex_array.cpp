#include "uepch.h"
#include "vertex_array.h"

#include "renderer.h"
#include "platform/opengl/opengl_vertex_array.h"

namespace Ugine
{
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::None:		UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
			case RendererAPI::OpenGL:	return new OpenGLVertexArray();
		}

		UE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
