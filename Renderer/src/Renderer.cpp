#include "Renderer.h"
#include <iostream>

void GlClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GlLogCall(const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGl Error] (" << error << ") " << file << " " << line << std::endl;
		return false;
	}
	std::cout << "[No OpenGl Errors Ocurred]" << file << " " << line << std::endl;
	return true;
}

void Renderer::Draw(const VertexArray & va, const IndexBuffer & ib, const Shader & shader) const
{
	va.Bind();
	ib.Bind();
	shader.Bind();

	glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
}

void Renderer::Clear()
{
	//clears screen
	glClear(GL_COLOR_BUFFER_BIT); 
}
