#include "uepch.h"
#include "render_command.h"

#include "platform/opengl/opengl_renderer_api.h"

namespace Ugine
{
	RendererAPI* RenderCommand::sRendererAPI = new OpenGLRendererAPI;
}