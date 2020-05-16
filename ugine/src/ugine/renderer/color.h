#pragma once

#include <glm/glm.hpp>

namespace Ugine
{
	class Color
	{
	public:
		static glm::vec4 White() { return { 1.0f, 1.0f, 1.0f, 1.0f }; }
		static glm::vec4 Red() { return { 1.0f, 0.0f, 0.0f, 1.0f }; }
		static glm::vec4 Blue() { return { 0.0f, 0.0f, 1.0f, 1.0f }; }
		static glm::vec4 Yellow() { return { 0.9f, 1.0f, 0.2f, 1.0f }; }
	};
}