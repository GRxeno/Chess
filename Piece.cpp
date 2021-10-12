#include "Piece.h"

float start_position[] = {
//A8
-1.0f,0.75f,
-0.75f,0.75f,
-0.75f,1.0f,
-0.75f,1.0f,
-1.0f,1.0f,
-1.0f,0.75f,
};

float texturePos[] = {
    0.0f,0.0f, //Bottom Left
    1.0f,0.0f, //Bottom Right
    1.0f,1.0f, //Top Left
    1.0f,1.0f, //Top Left
    0.0f,1.0f, //Top Right
};

Piece::Piece(unsigned int type)
    :type(type), isColor(0), translation(0), initState(true),  currentRow(0), currentColumn(0)
{ 

    VertexBufferLayout layout; 
    layout.Push(2);
    layout.Push(2);

    va = new VertexArray{};
    VertexBuffer vbt = VertexBuffer(texturePos, sizeof(texturePos));          
    VertexBuffer vb = VertexBuffer(start_position, sizeof(start_position));
    va->AddBuffer(vb, layout, 0);
    va->AddBuffer(vbt, layout, 1);
    va->Unbind();
    vb.Unbind();

    if (type >= 7 && type <= 12)
        isColor = Black_Piece;
    else if (type > 0 && type <=6)
        isColor = White_Piece;

    switch(type) {
        case Black_Pawn:
        {
            texture = new Texture("resources/textures/Chess_BP.png");
            // textureID = 0;
            break;
        }
        case Black_Rook:
        {
            texture = new Texture("resources/textures/Chess_BR.png");
            // textureID = 1;
            break;
        }
        case Black_Bishop:
        {
            texture = new Texture("resources/textures/Chess_BB.png");
            // textureID = 2;
            break;
        }
        case Black_Knight:
        {
            texture = new Texture("resources/textures/Chess_BN.png");
            // textureID = 3;
            break;
        }
        case Black_Queen:
        {
            texture = new Texture("resources/textures/Chess_BQ.png");
            // textureID = 4;
            break;
        }
        case Black_King:
        {
            texture = new Texture("resources/textures/Chess_BK.png");
            // textureID = 5;
            break;
        }
        
        case White_Pawn:
        {
            texture = new Texture("resources/textures/Chess_WP.png");
            // textureID = 6;
            break;
        }
        case White_Rook:
        {
            texture = new Texture("resources/textures/Chess_WR.png");
            // textureID = 7;
            break;
        }
        case White_Bishop:
        {
            texture = new Texture("resources/textures/Chess_WB.png");
            // textureID = 8;
            break;
        }
        case White_Knight:
        {
            texture = new Texture("resources/textures/Chess_WN.png");
            // textureID = 9;
            break;
        }
        case White_Queen:
        {
            texture = new Texture("resources/textures/Chess_WQ.png");
            // textureID = 10;
            break;
        }
        case White_King:
        {
            texture = new Texture("resources/textures/Chess_WK.png");
            // textureID = 11;
            break;
        }
    }
}

Piece::~Piece(){
    delete this;
}

void Piece::Draw(const Renderer& renderer, Shader& shader){
    glm::mat4 Model = glm::translate(glm::mat4(1.0f), translation);
	shader.SetUniformMatrix4f("u_Model", Model);
    texture->Bind(0);
    renderer.Draw(*va, shader);
}

/**
*@Move
*Moves a Piece
*/
bool Piece::Move(int row, int column){

    bool validMove = false;

    switch(type) {
            case Black_Pawn:
            {
                if (column == currentColumn){
                    if (initState){
                        if (row - currentRow <= 2 && row - currentRow >= 0){
                            validMove = true;
                            initState = false;
                        }
                    }
                    else {
                       if (row - currentRow <= 1 && row - currentRow >= 0)
                            validMove = true;
                    }
                }
                break;
            }
            // case Black_Rook:
            // {
            //     DoMove(row, column);
            //     break;
            // }
            // case Black_Bishop:
            // {
            //     DoMove(row, column);
            //     break;
            // }
            // case Black_Knight:
            // {
            //     DoMove(row, column);
            //     break;
            // }
            // case Black_Queen:
            // {
            //     DoMove(row, column);
            //     break;
            // }
            // case Black_King:
            // {
            //     DoMove(row, column);
            //     break;
            // }
            
            case White_Pawn:
            {
                if (column == currentColumn){
                    if (initState){
                        if (currentRow - row <= 2 && currentRow - row >= 0){
                            validMove = true;
                            initState = false;
                        }
                    }
                    else {
                       if (currentRow - row <= 1 && currentRow - row >= 0)
                            validMove = true;
                    }
                }
                break;
            }
            // case White_Rook:
            // {
            //     DoMove(row, column);
            //     break;
            // }
            // case White_Bishop:
            // {
            //     DoMove(row, column);
            //     break;
            // }
            // case White_Knight:
            // {
            //     DoMove(row, column);
            //     break;
            // }
            // case White_Queen:
            // {
            //     DoMove(row, column);
            //     break;
            // }
            // case White_King:
            // {
            //     DoMove(row, column);
            //     break;
            // }
                default:
                {
                    std::cout << "TYPE: " << type << std::endl;
                    DoMove(row, column);
                    validMove = true;
                }
        }

        if (validMove)
            DoMove(row, column);
        return validMove;
}

void Piece::DoMove(int row, int column){
    currentColumn = column;
    currentRow = row;
    translation.x = (float)column * 0.25f;
    translation.y = -((float)row * 0.25f);
}