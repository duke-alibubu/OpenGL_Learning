#pragma once

#include <GL/glew.h>

#include  "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

void clearError();
void checkError();

class Renderer
{
private:

public:
	void clear() const;
	void draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
};