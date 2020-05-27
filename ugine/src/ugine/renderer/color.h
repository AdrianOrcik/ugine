#pragma once

#include <glm/glm.hpp>

namespace Ugine
{
	class Color
	{
	public:
		//static glm::vec4 White() { return { 1.0f, 1.0f, 1.0f, 1.0f }; }
		//static glm::vec4 Green() { return { 0.02f, 0.8f, 0.0f, 1.0f }; }
		//static glm::vec4 Red() { return { 1.0f, 0.0f, 0.0f, 1.0f }; }
		//static glm::vec4 Blue() { return { 0.0f, 0.0f, 1.0f, 1.0f }; }
		//static glm::vec4 Yellow() { return { 0.9f, 1.0f, 0.2f, 1.0f }; }
		//static glm::vec4 Purple() { return { 1.0f, 0.121f, 0.917f, 1.0f }; }

		static glm::vec4 Background() { return { 0.090f, 0.215f, 0.325f, 1.0f };}
		static glm::vec4 DefaultElement() { return { 0.2f,0.631f,0.992f, 1.0f }; }
		static glm::vec4 SelectElement() { return { 0.239f,0.980f,1.0f, 1.0f }; }
		static glm::vec4 MoveElement() { return { 0.992f,0.792f,0.250f, 1.0f }; }
		static glm::vec4 SortedElement() { return { 0.968f,0.596f,0.141f, 1.0f }; }
		static glm::vec4 SelectRange() { return { 0.972f,0.631f,0.219f, 1.0f }; }
	};
}