#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID;  //an ID for every kind of object we allocate in OpenGL. I.e: Creating a buffer, shader,v..v it gets some kind of ID- and ID that identifies it
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void bind();
	void unbind();
};
