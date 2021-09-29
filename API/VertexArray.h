#pragma once

#include "VertexBuffer.h"
#include "Shader.h"
#include "VertexBufferLayout.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
using namespace glm;

class VertexArray
{
private:
	unsigned int m_RenderedID;
	int m_VerticesNum;
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout, const int layoutID);
	void Draw(Shader& shader);

	void Bind() const;
	void Unbind() const;

	inline int GetVertices() const { return m_VerticesNum; }
};