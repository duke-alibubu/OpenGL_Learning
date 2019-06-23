#include "Renderer.h"
#include <iostream>

void clearError()
{
	while (glGetError() != GL_NO_ERROR);
}

void checkError()
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGL_Error] (" << error << ")" << std::endl;
	}
}

void Renderer::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT);
}


void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const 
{
	shader.bind();

	va.bind();
	ib.bind();

	glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr);		//draw the triangle. 6 = number of indices. Nullptr cause we have 
																				//alr bounded ibo to GL_ELEMENT_ARRAY_BUFFER
																				//If did not bound ibo to GL_ELEMENT_ARRAY_BUFFER have to specify "indices"
																				//Have to be unsigned int, because buffer's made up of unsigned int	
}