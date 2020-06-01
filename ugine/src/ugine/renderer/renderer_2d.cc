#include "uepch.h"
#include "renderer_2d.h"

#include "vertex_array.h"
#include "shader.h"
#include "render_command.h"

#include "platform/opengl/opengl_shader.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Ugine
{
	Renderer2DStorage* Renderer2D::Data = nullptr;
	void Renderer2D::Init()
	{
		Data = DBG_NEW Renderer2DStorage();
		Data->VertexArray = VertexArray::Create();

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

		Data->VertexArray->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Ref<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		Data->VertexArray->SetIndexBuffer(squareIB);

		Data->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		Data->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		Data->TextureShader = Shader::Create("assets/shaders/Texture.glsl");
		Data->TextureShader->Bind();
		Data->TextureShader->SetInt("uTexture", 2);
	}

	void Renderer2D::Shutdown()
	{
		delete Data;
	}

	void Renderer2D::OnBegin(const OrthographicCamera & camera)
	{
		Data->TextureShader->Bind();
		Data->TextureShader->SetMat4("uViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::OnEnd()
	{
	}
	
	void Renderer2D::Draw(const glm::vec2 & position, const glm::vec2 & size, const glm::vec4 & color) 
	{
		Draw({ position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::Draw(const glm::vec3 & position, const glm::vec2 & size, const glm::vec4 & color)
	{
		Data->TextureShader->SetFloat4("uColor", color);
		Data->WhiteTexture->Bind();
	
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		Data->TextureShader->SetMat4("uTransform", transform);

		Data->VertexArray->Bind();
		RenderCommand::DrawIndexed(Data->VertexArray);
	}

	void Renderer2D::Draw(const glm::vec2 & position, const glm::vec2 & size, const Ref<Texture2D> texture)
	{
		Draw({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::Draw(const glm::vec3 & position, const glm::vec2 & size, const Ref<Texture2D> texture)
	{
		Data->TextureShader->SetFloat4("uColor", glm::vec4(1.0f));
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		Data->TextureShader->SetMat4("uTransform", transform);

		Data->VertexArray->Bind();
		RenderCommand::DrawIndexed(Data->VertexArray);
	}

}