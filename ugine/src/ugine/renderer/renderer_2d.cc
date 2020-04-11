#include "uepch.h"
#include "renderer_2d.h"

#include "vertex_array.h"
#include "shader.h"
#include "render_command.h"

#include "platform/opengl/opengl_shader.h"

namespace Ugine
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> VertexArray;
		Ref<Shader> Shader;
	};

	static Renderer2DStorage* data_;

	void Renderer2D::Init()
	{
		data_ = new Renderer2DStorage();
		data_->VertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ShaderDataType::Float3, "aPosition"}
		});
		data_->VertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
		Ref<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		data_->VertexArray->SetIndexBuffer(squareIB);

		data_->Shader = Shader::Create("assets/shaders/FlatColor.glsl");
	}

	void Renderer2D::Shutdown()
	{
		delete data_;
	}

	void Renderer2D::BegineScene(const OrthographicCamera & camera)
	{
		std::dynamic_pointer_cast<OpenGLShader>(data_->Shader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(data_->Shader)->SetUniformMat4("uViewProjection", camera.GetViewProjectionMatrix());
		std::dynamic_pointer_cast<OpenGLShader>(data_->Shader)->SetUniformMat4("uTransform", glm::mat4(1.0f));
	}

	void Renderer2D::EndScene()
	{
	}

	void Renderer2D::DrawQuad(const glm::vec2 & position, const glm::vec2 & size, const glm::vec4 & color)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::DrawQuad(const glm::vec3 & position, const glm::vec2 & size, const glm::vec4 & color)
	{
		std::dynamic_pointer_cast<OpenGLShader>(data_->Shader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(data_->Shader)->SetUniformFloat4("uColor", color);

		data_->VertexArray->Bind();
		RenderCommand::DrawIndexed(data_->VertexArray);
	}

}