#pragma once

#include "API/VertexArray.h"
#include "API/Renderer.h"

class Board {

    private:
        float *arr[32];
        glm::mat4 Model;
        // std::vector<VertexArray*> Boxes;
        // VertexArray* BoxesArray[64];

    public:
        Board();
        void PrintBoard(int number);
        void Draw(const Renderer& renderer, Shader& shader);

        float* ReturnBoard(int number){ return arr[number]; }

};