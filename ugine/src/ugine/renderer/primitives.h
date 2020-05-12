#pragma once
#include <stdint.h>

namespace Ugine
{
	struct PrimitiveData
	{
		float *Vertices;
		uint32_t *Indices;
		uint32_t VerticesSize;
		uint32_t IndicesSize;

		PrimitiveData(float *vertices, uint32_t verticesSize, uint32_t *indices, uint32_t indicesSize) 
			:Vertices(vertices), VerticesSize(verticesSize), Indices(indices), IndicesSize(indicesSize)
		{}

		~PrimitiveData()
		{
			delete Vertices;
			delete Indices;
		}
	};

	enum PrimitiveType { Square };
	class Primitives
	{
	public:
		static PrimitiveData* Generate(PrimitiveType type)
		{
			PrimitiveData *data;
			switch (type)
			{
			case Ugine::Square:
				data = GenerateSquare();
				break;
			default:
				break;
			}

			return data;
		}
	private:
		static PrimitiveData* GenerateSquare()
		{
			//TODO: memory leak
			float *squareVertices = DBG_NEW float[5 * 4]{
				-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
				 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
				 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
				-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
			};

			//TODO: memory leak
			uint32_t *squareIndices = DBG_NEW uint32_t[6]{ 0,1,2,2,3,0 };
			return new PrimitiveData(squareVertices, 20, squareIndices, 6);
		}
	};
}