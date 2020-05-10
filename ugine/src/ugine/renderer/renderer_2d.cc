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
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	static Renderer2DStorage* data_;

	void Renderer2D::Init(RendererStaticData* rendererStaticData)
	{
		data_ = DBG_NEW Renderer2DStorage();
		data_->VertexArray = VertexArray::Create();

		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(rendererStaticData->primitiveData->Vertices, 
			sizeof(rendererStaticData->primitiveData->Vertices) * rendererStaticData->primitiveData->VerticesSize));

		squareVB->SetLayout({
			{ShaderDataType::Float3, "aPosition"},
			{ShaderDataType::Float2, "aTexCoord"},
		});

		data_->VertexArray->AddVertexBuffer(squareVB);

		Ref<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(rendererStaticData->primitiveData->Indices, 
			(sizeof(rendererStaticData->primitiveData->Indices) * rendererStaticData->primitiveData->IndicesSize) / sizeof(uint32_t)));
		data_->VertexArray->SetIndexBuffer(squareIB);

		data_->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		data_->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		data_->TextureShader = Shader::Create(rendererStaticData->shaderPath);
		data_->TextureShader->Bind();
		data_->TextureShader->SetInt("uTexture", 2);
	}

	void Renderer2D::Shutdown()
	{
		delete data_;
	}

	void Renderer2D::OnBegin(const OrthographicCamera & camera)
	{
		data_->TextureShader->Bind();
		data_->TextureShader->SetMat4("uViewProjection", camera.GetViewProjectionMatrix());
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
		data_->TextureShader->SetFloat4("uColor", color);
		data_->WhiteTexture->Bind();
	
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		data_->TextureShader->SetMat4("uTransform", transform);

		data_->VertexArray->Bind();
		RenderCommand::DrawIndexed(data_->VertexArray);
	}

	void Renderer2D::Draw(const glm::vec2 & position, const glm::vec2 & size, const Ref<Texture2D> texture)
	{
		Draw({ position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::Draw(const glm::vec3 & position, const glm::vec2 & size, const Ref<Texture2D> texture)
	{
		data_->TextureShader->SetFloat4("uColor", glm::vec4(1.0f));
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		data_->TextureShader->SetMat4("uTransform", transform);

		data_->VertexArray->Bind();
		RenderCommand::DrawIndexed(data_->VertexArray);
	}

}