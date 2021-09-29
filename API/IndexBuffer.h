#pragma once

#include <GL/glew.h>

class IndexBuffer
{
private: 
	unsigned int m_RendererID;
	int m_Count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	inline int GetCount() const { return m_Count; }
};