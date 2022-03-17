#pragma once

#include <GL/glew.h>
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

void GlClearError();

//Prints to the console any OpenGl error that has ocurred
bool GlLogCall(const char* file, int line);


class Renderer
{
public:
	void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;
	void Clear();
};