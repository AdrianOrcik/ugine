#include "uepch.h"
#include "renderer_2d.h"

#include "vertex_array.h"
#include "shader.h"
#include "render_command.h"

#include "platform/opengl/opengl_shader.h"
#include <glm/gtc/matrix_transform.hpp>

namespace Ugine
{

	void Renderer2D::Init(RendererStaticData* rendererStaticData)
	{
		//TODO: memory leak
		rendererStaticData->renderer2DStorage = DBG_NEW Renderer2DStorage();
		rendererStaticData->renderer2DStorage->VertexArray = VertexArray::Create();

		Ref<VertexBuffer> squareVB;
		squareVB.reset(VertexBuffer::Create(rendererStaticData->primitiveData->Vertices, 
			sizeof(rendererStaticData->primitiveData->Vertices) * rendererStaticData->primitiveData->VerticesSize));

		squareVB->SetLayout({
			{ShaderDataType::Float3, "aPosition"},
			{ShaderDataType::Float2, "aTexCoord"},
		});

		rendererStaticData->renderer2DStorage->VertexArray->AddVertexBuffer(squareVB);

		Ref<IndexBuffer> squareIB;
		squareIB.reset(IndexBuffer::Create(rendererStaticData->primitiveData->Indices, 
			(sizeof(rendererStaticData->primitiveData->Indices) * rendererStaticData->primitiveData->IndicesSize) / sizeof(uint32_t)));
		rendererStaticData->renderer2DStorage->VertexArray->SetIndexBuffer(squareIB);

		rendererStaticData->renderer2DStorage->WhiteTexture = Texture2D::Create(1, 1);
		uint32_t whiteTextureData = 0xffffffff;
		rendererStaticData->renderer2DStorage->WhiteTexture->SetData(&whiteTextureData, sizeof(uint32_t));

		rendererStaticData->renderer2DStorage->TextureShader = Shader::Create(rendererStaticData->shaderPath);
		rendererStaticData->renderer2DStorage->TextureShader->Bind();
		rendererStaticData->renderer2DStorage->TextureShader->SetInt("uTexture", 2);
	}

	void Renderer2D::Shutdown()
	{
		//delete data_;
	}

	void Renderer2D::OnBegin(Renderer2DStorage* renderer2DStorage, const OrthographicCamera & camera)
	{
		renderer2DStorage->TextureShader->Bind();
		renderer2DStorage->TextureShader->SetMat4("uViewProjection", camera.GetViewProjectionMatrix());
	}

	void Renderer2D::OnEnd()
	{
	}

	void Renderer2D::Draw(Renderer2DStorage* renderer2DStorage, const glm::vec2 & position, const glm::vec2 & size, const glm::vec4 & color)
	{
		Draw(renderer2DStorage, { position.x, position.y, 0.0f }, size, color);
	}

	void Renderer2D::Draw(Renderer2DStorage* renderer2DStorage, const glm::vec3 & position, const glm::vec2 & size, const glm::vec4 & color)
	{
		renderer2DStorage->TextureShader->SetFloat4("uColor", color);
		renderer2DStorage->WhiteTexture->Bind();
	
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		renderer2DStorage->TextureShader->SetMat4("uTransform", transform);

		renderer2DStorage->VertexArray->Bind();
		RenderCommand::DrawIndexed(renderer2DStorage->VertexArray);
	}

	void Renderer2D::Draw(Renderer2DStorage* renderer2DStorage, const glm::vec2 & position, const glm::vec2 & size, const Ref<Texture2D> texture)
	{
		Draw(renderer2DStorage, { position.x, position.y, 0.0f }, size, texture);
	}

	void Renderer2D::Draw(Renderer2DStorage* renderer2DStorage, const glm::vec3 & position, const glm::vec2 & size, const Ref<Texture2D> texture)
	{
		renderer2DStorage->TextureShader->SetFloat4("uColor", glm::vec4(1.0f));
		texture->Bind();

		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
		renderer2DStorage->TextureShader->SetMat4("uTransform", transform);

		renderer2DStorage->VertexArray->Bind();
		RenderCommand::DrawIndexed(renderer2DStorage->VertexArray);
	}

}