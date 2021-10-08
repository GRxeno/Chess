#pragma once

#include "API/VertexArray.h"
#include "API/Texture.h"
#include "API/Renderer.h"

enum PieceID {
    White_Pawn = 1,
    White_Rook = 2,
    White_Bishop = 3,
    White_Knight = 4,
    White_Queen = 5,
    White_King = 6,
    
    Black_Pawn = 7,
    Black_Rook = 8,
    Black_Bishop = 9,
    Black_Knight = 10,
    Black_Queen = 11,
    Black_King = 12,
}; 

class Piece {

    private:
        unsigned int type;
        int textureID;
        VertexArray* va;
        Texture* texture;
        glm::vec3 translation;
        int currentRow, currentColumn;
        bool initState;

    public:
        Piece(unsigned int type = 0);
        ~Piece();
        void Draw(const Renderer& renderer, Shader& shader);
        bool Move(int row, int column);
        void DoMove(int row, int column);
        
        inline VertexArray* getPieceVa() { return va; }
        inline unsigned int getType() { return type; }
        inline float* getTranslation() { return &translation.x; }
        inline void setTranslation(glm::vec3 translation) { translation = translation; }
};