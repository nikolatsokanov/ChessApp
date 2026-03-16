#include <iostream>
#include <string>
#include <vector>
using namespace std;
#include "raylib.h"

const int TILE = 100;

void DrawChessBoard(string chessboard[9][9],
                    Texture2D whiteSquare, Texture2D blackSquare,
                    Texture2D wPawn, Texture2D bPawn,
                    Texture2D wRook, Texture2D bRook,
                    Texture2D wQueen, Texture2D bQueen,
                    Texture2D wKing, Texture2D bKing,
                    Texture2D wBishop, Texture2D bBishop,
                    Texture2D wKnight, Texture2D bKnight);


int main() {
    string chessboard[9][9] = {
        {" ", "1","2","3","4","5","6","7","8"},
        {"1","r","n","b","q","k","b","n","r"},
        {"2","p","p","p","p","p","p","p","p"},
        {"3",".",".",".",".",".",".",".","."},
        {"4",".",".",".",".",".",".",".","."},
        {"5",".",".",".",".",".",".",".","."},
        {"6",".",".",".",".",".",".",".","."},
        {"7","P","P","P","P","P","P","P","P"},
        {"8","R","N","B","Q","K","B","N","R"}
    };
    
    
string takenPiece;
string piece;

bool whiteToMove = true;

    
    InitWindow(800, 800, "Chess");
    SetTargetFPS(60);
  

    // Load piece textures
    Texture2D wPawn = LoadTexture("textures/white-pawn.png");
    Texture2D bPawn = LoadTexture("textures/black-pawn.png");
    Texture2D wRook = LoadTexture("textures/white-rook.png");
    Texture2D bRook = LoadTexture("textures/black-rook.png");
    Texture2D wQueen = LoadTexture("textures/white-queen.png");
    Texture2D bQueen = LoadTexture("textures/black-queen.png");
    Texture2D wKing = LoadTexture("textures/white-king.png");
    Texture2D bKing = LoadTexture("textures/black-king.png");
    Texture2D wKnight = LoadTexture("textures/white-knight.png");
    Texture2D bKnight = LoadTexture("textures/black-knight.png");
    Texture2D wBishop = LoadTexture("textures/white-bishop.png");
    Texture2D bBishop = LoadTexture("textures/black-bishop.png");

    // Square textures
    Texture2D whiteSquare = LoadTexture("textures/light_square.png");
    Texture2D blackSquare = LoadTexture("textures/dark_square.png");


    while (!WindowShouldClose()) {


        //piece selection and placement locations
        int right = -1, down = -1;
        int dropRight = -1, dropDown = -1;
        bool moveAttempted = false;
        // only run move validation when the user actually tries to move
        static int selectedX = -1, selectedY = -1;

            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                Vector2 mouse = GetMousePosition();
                int clickedX = (int)(mouse.x / TILE) + 1;
                int clickedY = (int)(mouse.y / TILE) + 1;

                if (clickedX >= 1 && clickedX <= 8 && clickedY >= 1 && clickedY <= 8) {
                    if (selectedX == -1) {
                        if (chessboard[clickedY][clickedX] != ".") {
                            selectedX = clickedX;
                            selectedY = clickedY;
                        }
                    } else {
                        down = selectedX; right = selectedY;
                        dropDown = clickedX; dropRight = clickedY;

                        piece = chessboard[right][down];
                        takenPiece = chessboard[dropRight][dropDown];
                        moveAttempted = true;

                        selectedX = -1;
                        selectedY = -1;
                    }
                }
            }
        
        if (!moveAttempted) {

            BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawChessBoard(chessboard, whiteSquare, blackSquare, wPawn, bPawn, wRook, bRook, wQueen, bQueen, wKing, bKing, wBishop, bBishop, wKnight, bKnight);
            DrawText(whiteToMove ? "White to move" : "Black to move", 10, 10, 20, BLACK);
            EndDrawing();
            continue;
        }

        chessboard[right][down] = ".";
        chessboard[dropRight][dropDown] = piece;

        //draw board
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawChessBoard(chessboard, whiteSquare, blackSquare, wPawn, bPawn, wRook, bRook, wQueen, bQueen, wKing, bKing, wBishop, bBishop, wKnight, bKnight);
        DrawText(whiteToMove ? "White to move" : "Black to move", 10, 10, 20, BLACK);
        EndDrawing();
    }
    CloseWindow();

    return 0;
}




void DrawChessBoard(string chessboard[9][9],
                    Texture2D whiteSquare, Texture2D blackSquare,
                    Texture2D wPawn, Texture2D bPawn,
                    Texture2D wRook, Texture2D bRook,
                    Texture2D wQueen, Texture2D bQueen,
                    Texture2D wKing, Texture2D bKing,
                    Texture2D wBishop, Texture2D bBishop,
                    Texture2D wKnight, Texture2D bKnight)
{
    for (int y = 1; y <= 8; y++) {
        for (int x = 1; x <= 8; x++) {
            // Draw square texture
            if ((x + y) % 2 == 0)
                DrawTextureEx(whiteSquare, (Vector2){(float)(x-1)*TILE, (float)(y-1)*TILE}, 0, (float)TILE / whiteSquare.width, WHITE);
            else
                DrawTextureEx(blackSquare, (Vector2){(float)(x-1)*TILE, (float)(y-1)*TILE}, 0, (float)TILE / blackSquare.width, WHITE);

            // Draw pieces
            string piece = chessboard[y][x];
            if (piece == "P") {
                DrawTextureEx(wPawn, (Vector2){(float)(x-1)*TILE, (float)(y-1)*TILE}, 0, (float)TILE / wPawn.width, WHITE);
            } else if (piece == "p") {
                DrawTextureEx(bPawn, (Vector2){(float)(x-1)*TILE, (float)(y-1)*TILE}, 0, (float)TILE / bPawn.width, WHITE);
            } else if (piece == "R") {
                DrawTextureEx(wRook, (Vector2){(float)(x-1)*TILE, (float)(y-1)*TILE}, 0, (float)TILE / wRook.width, WHITE);
            } else if (piece == "r") {
                DrawTextureEx(bRook, (Vector2){(float)(x-1)*TILE, (float)(y-1)*TILE}, 0, (float)TILE / bRook.width, WHITE);
            } else if (piece == "N") {
                DrawTextureEx(wKnight, (Vector2){(float)(x-1)*TILE, (float)(y-1)*TILE}, 0, (float)TILE / wKnight.width, WHITE);
            } else if (piece == "n") {
                DrawTextureEx(bKnight, (Vector2){(float)(x-1)*TILE, (float)(y-1)*TILE}, 0, (float)TILE / bKnight.width, WHITE);
            } else if (piece == "B") {
                DrawTextureEx(wBishop, (Vector2){(float)(x-1)*TILE, (float)(y-1)*TILE}, 0, (float)TILE / wBishop.width, WHITE);
            } else if (piece == "b") {
                DrawTextureEx(bBishop, (Vector2){(float)(x-1)*TILE, (float)(y-1)*TILE}, 0, (float)TILE / bBishop.width, WHITE);
            } else if (piece == "Q") {
                DrawTextureEx(wQueen, (Vector2){(float)(x-1)*TILE, (float)(y-1)*TILE}, 0, (float)TILE / wQueen.width, WHITE);
            } else if (piece == "q") {
                DrawTextureEx(bQueen, (Vector2){(float)(x-1)*TILE, (float)(y-1)*TILE}, 0, (float)TILE / bQueen.width, WHITE);
            } else if (piece == "K") {
                DrawTextureEx(wKing, (Vector2){(float)(x-1)*TILE, (float)(y-1)*TILE}, 0, (float)TILE / wKing.width, WHITE);
            } else if (piece == "k") {
                DrawTextureEx(bKing, (Vector2){(float)(x-1)*TILE, (float)(y-1)*TILE}, 0, (float)TILE / bKing.width, WHITE);
            }
        }
    }
}
