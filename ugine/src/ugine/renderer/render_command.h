#pragma once

#include "renderer_api.h"

namespace Ugine
{

	class RenderCommand
	{
	public:
		inline static void SetClearColor(const glm::vec4& color)
		{
			sRendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			sRendererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			sRendererAPI->DrawIndexed(vertexArray);
		}

	private:
		static RendererAPI* sRendererAPI;
	};


}