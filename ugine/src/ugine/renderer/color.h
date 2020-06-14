#pragma once

#include <glm/glm.hpp>

namespace Ugine
{
	class Color
	{
	public:
		// basic color pallete
		static glm::vec4 White() { return { 1.0f, 1.0f, 1.0f, 1.0f }; }
		static glm::vec4 Green() { return { 0.02f, 0.8f, 0.0f, 1.0f }; }
		static glm::vec4 Red() { return { 1.0f, 0.0f, 0.0f, 1.0f }; }
		static glm::vec4 Blue() { return { 0.0f, 0.0f, 1.0f, 1.0f }; }
		static glm::vec4 Yellow() { return { 0.9f, 1.0f, 0.2f, 1.0f }; }
		static glm::vec4 Purple() { return { 1.0f, 0.121f, 0.917f, 1.0f }; }

		// sorting project color pallete
		static glm::vec4 Background() { return { 0.090f, 0.215f, 0.325f, 1.0f };}
		//static glm::vec4 DefaultElement() { return { 0.2f,0.631f,0.992f, 1.0f }; }
		//static glm::vec4 SelectElement() { return { 0.239f,0.980f,1.0f, 1.0f }; }
		//static glm::vec4 MoveElement() { return { 0.992f,0.792f,0.250f, 1.0f }; }
		//static glm::vec4 SortedElement() { return { 0.968f,0.596f,0.141f, 1.0f }; }
		//static glm::vec4 SelectRange() { return { 0.972f,0.631f,0.219f, 1.0f }; }

		// pathfinding project color pallete
		//static glm::vec4 Background() { return { 0.168f, 0.619f, 0.701f, 1.0f }; }	// blue munsell
		//static glm::vec4 Background() { return { 0.858f, 0.835f, 0.709f, 1.0f }; }
		//static glm::vec4 StartNode() { return { 0.733f, 0.870f, 0.941f, 1.0f }; }	// columbia
		//static glm::vec4 RegularNode() { return { 0.858f, 0.835f, 0.709f, 1.0f }; } // dutch white
		//static glm::vec4 FinalNode() { return { 0.266f, 0.686f, 0.411f, 1.0f }; }	// medium sea
		//static glm::vec4 WallNode() { return { 0.972f, 0.2f, 0.235f, 1.0f }; }		// red salsa
		//static glm::vec4 PathNode() { return { 0.988f, 0.670f, 0.062f, 1.0f }; }	// bright yellow
		//static glm::vec4 SelectNode() { return { 0.227f, 0.376f, 0.431f, 1.0f }; }	// DeepSpace
	};
}