#include "uepch.h"
#include "renderer.h"

namespace Ugine
{
	//// todo: automatic assign by platform in runtime
	//RendererAPI Renderer::sRendererAPI_ = RendererAPI::OpenGL;

	void Renderer::BeginScene()
	{

	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray) 
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}