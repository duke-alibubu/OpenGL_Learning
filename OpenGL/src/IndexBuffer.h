#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererID;  //an ID for every kind of object we allocate in OpenGL. I.e: Creating a buffer, shader,v..v it gets some kind of ID- and ID that identifies it
	unsigned int m_Count; //how many indices
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void bind();
	void unbind();
	inline unsigned int getCount();
};
