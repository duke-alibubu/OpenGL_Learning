#pragma once
#include <vector>
#include <GL/glew.h>

struct VertexBufferElement 
{
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int getSizeOfType(unsigned int type)
	{
		switch (type)
		{
			case GL_FLOAT:	return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:  return 1;
			default:	break;
		}
		return 0;

	}
};
class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;	
	unsigned int m_Stride;
public:
	VertexBufferLayout() : m_Stride(0) {};

	template <typename T>
	void push(unsigned int count)
	{
		static_assert(false);
	}

	template<>
	void push<float>(unsigned int count)
	{
		m_Elements.push_back( {GL_FLOAT, count, GL_FALSE} );
		m_Stride += VertexBufferElement::getSizeOfType(GL_FLOAT) * count;
	}

	template<>
	void push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT) * count ;     //GLuint
	}

	template<>
	void push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE) * count ;    //GLbyte
	}

	inline const std::vector<VertexBufferElement> getElements() const& { return m_Elements; }
	inline unsigned int getStride() const { return m_Stride; }        

};