#pragma once

#include "VertexArray.h"

#define ASSERT(x) if (!(x)) __debugbreak();

class Renderer
{
public:
	void ClearScreen() const;
	void Draw(const VertexArray& va, const Shader& shader) const;
};