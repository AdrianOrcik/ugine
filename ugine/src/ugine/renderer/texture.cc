#include "uepch.h"
#include "texture.h"

#include "renderer.h"
#include "platform/opengl/opengl_texture.h"

namespace Ugine
{
	Ref<Texture2D> Ugine::Texture2D::Create(const std::string & path)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    UE_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_shared<OpenGLTexture2D>(path);
		}

		UE_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
