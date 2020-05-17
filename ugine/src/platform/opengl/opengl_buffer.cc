#include "uepch.h"
#include "opengl_buffer.h"

#include <glad/glad.h>

// vertex buffer
// -------------
Ugine::OpenGLVertexBuffer::OpenGLVertexBuffer(float * vertices, uint32_t size)
{
	glCreateBuffers(1, &rendererID_);
	glBindBuffer(GL_ARRAY_BUFFER, rendererID_);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

Ugine::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(GL_ARRAY_BUFFER, &rendererID_);
}

void Ugine::OpenGLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, rendererID_);
}

void Ugine::OpenGLVertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

// index buffer
// ------------
Ugine::OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t * indices, uint32_t count)
	:count_(count)
{
	glCreateBuffers(1, &rendererID_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
}

Ugine::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	//TODO: sometimes trying to free null buffer
	glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &rendererID_);
}

void Ugine::OpenGLIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, rendererID_);
}

void Ugine::OpenGLIndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32_t Ugine::OpenGLIndexBuffer::GetCount() const
{
	return count_;
}