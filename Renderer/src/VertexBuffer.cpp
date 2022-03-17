#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void * data, unsigned int size)
{
	glGenBuffers(1, &m_Renderer_ID);
	glBindBuffer(GL_ARRAY_BUFFER, m_Renderer_ID);//selects which buffer is going to be used
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_Renderer_ID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_Renderer_ID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
