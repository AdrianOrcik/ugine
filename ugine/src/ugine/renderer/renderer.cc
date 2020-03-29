#include "uepch.h"
#include "renderer.h"

namespace Ugine
{
		
	Renderer::SceneData* Renderer::sSceneData_ = new Renderer::SceneData;

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
		shader->SetUniformMat4("uViewProjection", sSceneData_->ViewProjectionMatrix);
		shader->SetUniformMat4("uTransform", transform);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}