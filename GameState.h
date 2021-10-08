#pragma once

#include "API/VertexArray.h"
#include "Piece.h"
#include "Board.h"

// Include GLFW
#include <GLFW/glfw3.h>

class GameState {

private:
    int score;
    Board board;
    Piece* pieces[8][8];

public:
    GameState();
    void PrintState();
    void Draw(const Renderer& renderer, Shader& shader);
    void Move(int curRow, int curColumn, int row, int column);
    void CreatePiece(unsigned int type, int row, int column);
    bool LoadFromFEN(const char* FEN);
};