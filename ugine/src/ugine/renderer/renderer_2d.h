#pragma once
#pragma once 

#include "orthographic_camera.h"

#include "texture.h"

namespace Ugine
{
	class Renderer2D
	{
	public:
		static void Init();
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