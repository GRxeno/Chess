#include "GameState.h"

const char* StartingFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
const char* OnePieceFen = "k";
const char* TestFEN = "b4b2/2NRPp2/2kp4/3R4/7B/1Pp5/4p1P1/1K4n1 w - - 0 1";

GameState::GameState()
    :score(0), whosTurn(0)
{

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            pieces[i][j] = new Piece(0);

    LoadFromFEN(StartingFEN);
    // LoadFromFEN(OnePieceFen);
    // LoadFromFEN(TestFEN);
}

void GameState::PrintState(){
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            std::cout << pieces[i][j]->getType() << " | ";
        }
        std::cout << std::endl;
    }
}

void GameState::Draw(const Renderer& renderer, Shader& shader){
    shader.SetUniform1i("u_Textured", false);
    board.Draw(renderer, shader);
    shader.SetUniform1i("u_Textured", true);
    for(int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if(pieces[i][j]->getType() != 0){
                pieces[i][j]->Draw(renderer, shader);
            }
        }
    }
}

void GameState::Move(int curRow, int curColumn, int row, int column){
    if(whosTurn == pieces[curRow][curColumn]->getColor()){ // Don't move out if not your turn
        if(pieces[row][column]->getColor() != pieces[curRow][curColumn]->getColor()){ // Don't move on same color piece
            if(pieces[curRow][curColumn]->Move(row, column)){ // If the move is successful update array
                pieces[row][column] = pieces[curRow][curColumn];
                pieces[curRow][curColumn] = new Piece();
                toggleTurn();
                std::cout << " -------------------- " << std::endl;
                PrintState();
            }
        }
    }
}

void GameState::CreatePiece(unsigned int type, int row, int column){
    pieces[row][column] = new Piece(type);
    pieces[row][column]->DoMove(row, column);
}

bool GameState::LoadFromFEN(const char* FEN){
    int index = 0;
    int row = 0;
    int column = 0;

    while (FEN[index] != '\0'){

        if (FEN[index] == '/'){
            row++;
            column = 0;
        }
        else if (FEN[index] >= '1' && FEN[index] <= '9'){
            column += FEN[index] - '0';
        }
        else if (FEN[index] == 'r'){
            CreatePiece(Black_Rook, row, column);
            column++;
        }
        else if (FEN[index] == 'n'){
            CreatePiece(Black_Knight, row, column);
            column++;
        }
        else if (FEN[index] == 'b'){
            CreatePiece(Black_Bishop, row, column);
            column++;
        }
        else if (FEN[index] == 'q'){
            CreatePiece(Black_Queen, row, column);
            column++;
        }
        else if (FEN[index] == 'k'){
            CreatePiece(Black_King, row, column);
            column++;
        }
        else if (FEN[index] == 'p'){
            CreatePiece(Black_Pawn, row, column);
            column++;
        }
        else if (FEN[index] == 'R'){
            CreatePiece(White_Rook, row, column);
            column++;
        }
        else if (FEN[index] == 'N'){
            CreatePiece(White_Knight, row, column);
            column++;
        }
        else if (FEN[index] == 'B'){
            CreatePiece(White_Bishop, row, column);
            column++;
        }
        else if (FEN[index] == 'Q'){
            CreatePiece(White_Queen, row, column);
            column++;
        }
        else if (FEN[index] == 'K'){
            CreatePiece(White_King, row, column);
            column++;
        }
        else if (FEN[index] == 'P'){
            CreatePiece(White_Pawn, row, column);
            column++;
        }
        else if (FEN[index] == ' '){
            if (FEN[index+1] == 'w')
                whosTurn = White_Piece;
            else if (FEN[index+1] == 'b')
                whosTurn = Black_Piece;
            break;
        }

        index++;
    }


    return false;
}



