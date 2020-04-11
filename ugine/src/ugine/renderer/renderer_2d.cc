#include "uepch.h"
#include "renderer_2d.h"

#include "vertex_array.h"
#include "shader.h"
#include "render_command.h"

#include "platform/opengl/opengl_shader.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Ugine
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> VertexArray;
		Ref<Shader> ColorShader;
		Ref<Shader> TextureShader;
	};

	static Renderer2DStorage* data_;

	void Renderer2D::Init()
	{
		data_ = new Renderer2DStorage();
		data_->VertexArray = VertexArray::Create();

		float squareVertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ShaderDataType::Float3, "aPosition"},
			{ShaderDataType::Float2, "aTexCoord"},
		});

		data_->VertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0,1,2,2,3,0 };
		Ref<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		data_->VertexArray->SetIndexBuffer(squareIB);

		data_->ColorShader = Shader::Create("assets/shaders/FlatColor.glsl");

		data_->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		data_->TextureShader->Bind();
		data_->TextureShader->SetInt("uTexture", 0);
	}

	void Renderer2D::Shutdown()
	{
		delete data_;
	}

	void Renderer2D::BegineScene(const OrthographicCamera & camera)
	{
		std::dynamic_pointer_cast<OpenGLShader>(data_->ColorShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(data_->ColorShader)->UploadUniformMat4("uViewProjection", camera.GetViewProjectionMatrix());

		std::dynamic_pointer_cast<OpenGLShader>(data_->TextureShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(data_->TextureShader)->UploadUniformMat4("uViewProjection", camera.GetViewProjectionMatrix());
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
		std::dynamic_pointer_cast<OpenGLShader>(data_->ColorShader)->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(data_->ColorShader)->UploadUniformFloat4("uColor", color);

		data_->ColorShader->Bind();
		data_->ColorShader->SetFloat4("uColor", color);

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		data_->ColorShader->SetMat4("uTransform", transform);

		data_->VertexArray->Bind();
		RenderCommand::DrawIndexed(data_->VertexArray);
	}

	void Renderer2D::DrawQuad(const glm::vec2 & position, const glm::vec2 & size, const Ref<Texture2D> texture)
	{
		DrawQuad({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::DrawQuad(const glm::vec3 & position, const glm::vec2 & size, const Ref<Texture2D> texture)
	{
		data_->TextureShader->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		data_->TextureShader->SetMat4("uTransform", transform);

		texture->Bind();

		data_->VertexArray->Bind();
		RenderCommand::DrawIndexed(data_->VertexArray);
	}

}