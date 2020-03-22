#pragma once

#include "ugine/renderer/vertex_array.h"

namespace Ugine
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		// Inherited via VertexArray
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

		virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return vertexBuffers_; }
		virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return indexBuffer_; }

	private:
		uint32_t rendererID_;
		std::vector<std::shared_ptr<VertexBuffer>> vertexBuffers_;
		std::shared_ptr<IndexBuffer> indexBuffer_;
	};
}