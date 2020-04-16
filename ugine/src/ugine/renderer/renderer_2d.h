#pragma once
#pragma once 

#include "orthographic_camera.h"

#include "texture.h"
#include "ugine/renderer/primitives.h"

namespace Ugine
{
	struct RendererStaticData
	{
		std::string shaderPath;
		std::string texturePath;
		struct PrimitiveData* primitiveData;
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

		static void BegineScene(const OrthographicCamera& camera);
		static void EndScene();

		// primitives
		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const glm::vec4& color);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const glm::vec4& color);

		static void DrawQuad(const glm::vec2& position, const glm::vec2& size, const Ref<Texture2D> texture);
		static void DrawQuad(const glm::vec3& position, const glm::vec2& size, const Ref<Texture2D> texture);

	};
}