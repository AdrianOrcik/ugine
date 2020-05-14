#pragma once
#pragma once 

#include "orthographic_camera.h"

#include "vertex_array.h"
#include "shader.h"
#include "texture.h"
#include "ugine/renderer/primitives.h"

namespace Ugine
{
	struct Renderer2DStorage
	{
		Ref<VertexArray> VertexArray;
		Ref<Shader> TextureShader;
		Ref<Texture2D> WhiteTexture;
	};

	struct RendererStaticData
	{
		std::string shaderPath;
		std::string texturePath;
		struct PrimitiveData* primitiveData;
		struct Renderer2DStorage* renderer2DStorage;

		~RendererStaticData()
		{
			delete primitiveData;
			delete renderer2DStorage;
		}
	};

	struct RendererDynamicData
	{
		glm::vec4 color;
		const OrthographicCamera* camera;
	};

	class Renderer2D
	{
	public:
		static void Init(RendererStaticData* rendererStaticData);
		static void Shutdown();

		static void OnBegin(Renderer2DStorage* renderer2DStorage, const OrthographicCamera& camera);
		static void OnEnd();

		// primitives
		static void Draw(Renderer2DStorage* renderer2DStorage, const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void Draw(Renderer2DStorage* renderer2DStorage, const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

		static void Draw(Renderer2DStorage* renderer2DStorage, const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture);
		static void Draw(Renderer2DStorage* renderer2DStorage, const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture);

	};
}