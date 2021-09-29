#include "Renderer.h"

void Renderer::ClearScreen() const
{
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
}

void Renderer::Draw(const VertexArray& va, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	glDrawArrays(GL_TRIANGLES, 0, va.GetVertices());
}
