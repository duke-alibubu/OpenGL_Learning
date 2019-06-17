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