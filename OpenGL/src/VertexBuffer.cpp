#include "VertexBuffer.h"

#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size) 
{
	glGenBuffers(1, &m_RendererID); //1 = no of buffers required. Generate Buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID); //bind the buffer - In this case, vertex attribute buffer
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); //creates and initializes a buffer object's data store
}

VertexBuffer::~VertexBuffer() 
{
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}