#pragma once
#include <stdint.h>

namespace Ugine
{
	//todo: refactor on more universal way
	struct PrimitiveData
	{
		float *vertices;
		uint32_t *indices;
	};

	enum PrimitiveType { Square };
	class Primitives
	{
	public:
		static PrimitiveData GenerateSquare()
		{
			float squareVertices[5 * 4] = {
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
				 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
				 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
				-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
			};

			uint32_t squareIndices[6] = { 0,1,2,2,3,0 };

			return{
				squareVertices,
				squareIndices
			};
		}
	};
}