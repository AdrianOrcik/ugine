#include "uepch.h"
#include "renderer.h"

#include "platform/opengl/opengl_shader.h"
#include "renderer_2d.h"

namespace Ugine
{
		
	//TODO: memory leak
	Renderer::SceneData* Renderer::sSceneData_ = DBG_NEW Renderer::SceneData;

	void Renderer::Init()
	{
		RenderCommand::Init();
		//Renderer2D::Init();
	}

	void Renderer::OnWindowResize(uint32_t width, uint32_t height)
	{
		RenderCommand::SetViewport(width, height);
	}

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		sSceneData_->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{

	}

	void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform)
	{
		shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("uViewProjection", sSceneData_->ViewProjectionMatrix);
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("uTransform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}