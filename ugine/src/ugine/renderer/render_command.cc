#include "uepch.h"
#include "render_command.h"

#include "platform/opengl/opengl_renderer_api.h"

namespace Ugine
{
	//TODO: memory leak
	RendererAPI* RenderCommand::sRendererAPI = DBG_NEW OpenGLRendererAPI;
}