#include "VertexArray.h"

#include <iostream>

VertexArray::VertexArray()
	: m_VerticesNum(0)
{
	glGenVertexArrays(1, &m_RenderedID);
}

VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &m_RenderedID);
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, const int layoutID)
{
	Bind();
	const auto& elements = layout.GetElements();
	glEnableVertexAttribArray(layoutID);
	vb.Bind();
	glVertexAttribPointer(layoutID, elements[layoutID].count, elements[layoutID].type, elements[layoutID].normanized, layout.GetStride(), (void*)0);
	if (layoutID == 0)
		m_VerticesNum += vb.GetLength() / 2;

}

void VertexArray::Draw(Shader& shader)
{
	Bind();
	shader.Bind();
	glDrawArrays(GL_TRIANGLES, 0, m_VerticesNum);
}

void VertexArray::Bind() const
{
	glBindVertexArray(m_RenderedID);
}

void VertexArray::Unbind() const
{
	glBindVertexArray(0);
}
