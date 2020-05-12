#include "uepch.h"
#include "buffer.h"

#include "renderer.h"
#include "ugine/log.h"

#include "platform/opengl/opengl_buffer.h"
#include "ugine/core.h"

namespace Ugine
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    UE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return DBG_NEW OpenGLVertexBuffer(vertices, size); //TODO: memory leak
		}

		UE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer * IndexBuffer::Create(uint32_t * indices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    UE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return DBG_NEW OpenGLIndexBuffer(indices, size); //TODO: memory leak
		}

		UE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}