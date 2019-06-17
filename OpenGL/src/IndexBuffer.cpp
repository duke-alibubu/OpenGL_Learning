#include "IndexBuffer.h"

#include "Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count):m_Count(count)
{
	glGenBuffers(1, &m_RendererID); //1 = no of buffers required. Generate Buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID); //bind the buffer - In this case, vertex attribute buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW); //creates and initializes a buffer object's data store
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::getCount()
{
	return m_Count;
}