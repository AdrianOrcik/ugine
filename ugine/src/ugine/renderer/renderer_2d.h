#pragma once

#include "orthographic_camera.h"

#include "vertex_array.h"
#include "shader.h"
#include "texture.h"

namespace Ugine
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> VertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void OnBegin(const OrthographicCamera& camera);
		static void OnEnd();

		// primitives
		static void Draw(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void Draw(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

		static void Draw(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture);
		static void Draw(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture);

		static Renderer2DStorage* Data;
	};
}