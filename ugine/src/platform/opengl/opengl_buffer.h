#pragma once

#include "ugine/renderer/buffer.h"

namespace Ugine
{

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		// Inherited via VertexBuffer
		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual const BufferLayout & GetLayout() const override { return layout_; }
		virtual void SetLayout(const BufferLayout & layout) override { layout_ = layout; };

	private: 
		uint32_t rendererID_;
		BufferLayout layout_;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();

		// Inherited via IndexBuffer
		virtual void Bind() const override;
		virtual void Unbind() const override;
		virtual uint32_t GetCount() const override;

	private:
		uint32_t rendererID_;
		uint32_t count_;
	};
}