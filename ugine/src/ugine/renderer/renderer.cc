#include "uepch.h"
#include "renderer.h"

namespace Ugine
{
	// todo: automatic assign by platform in runtime
	RendererAPI Renderer::sRendererAPI_ = RendererAPI::OpenGL;
}