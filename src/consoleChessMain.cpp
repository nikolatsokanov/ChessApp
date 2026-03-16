#include <iostream>
#include <string>
#include <vector>
using namespace std;

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

//after castling a simulation runs to check if the passing square is in check to decline and reverse the castle
string simulationWhiteMatrix[9][9];
string simulationBlackMatrix[9][9];
int programMoveOn = 0;
bool programMove = false;
int simulationWhiteKingRight;
int simulationWhiteKingDown;
int simulationBlackKingRight;
int simulationBlackKingDown;
bool simulationBlack = false;
bool simulationWhite = false;
bool simulationIsWhiteKingInCheck=false;
bool simulationIsBlackKingInCheck=false;
bool simulationWhiteKingStillInCheck=false;
bool simulationBlackKingStillInCheck=false;
bool simulationWhiteQueenSideCastle = false;
bool simulationWhiteKingSideCastle = false;
bool simulationBlackQueenSideCastle = false;
bool simulationBlackKingSideCastle = false;



    cout<<"White to move!"<<endl;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << chessboard[i][j] << " ";
        }
        cout << endl;
    }


int right, down;
//coordinates of the piece you want to move, 'right' are the numbers on the left and 'down' are the numbers on the top :)
bool enPassant = false;
int enPassantStillActive = 0;
int enPaassantSqaureRight = 0, enPassantSqaureDown = 0;
bool isWhiteKingInCheck=false;
bool isBlackKingInCheck=false;
bool whiteKingStillInCheck=false;
bool blackKingStillInCheck=false;
string takenPiece;
bool whiteKingSideCastle = true;
bool blackKingSideCastle = true;
bool whiteQueenSideCastle = true;
bool blackQueenSideCastle = true;
bool whiteKingMoved = false;
bool blackKingMoved = false;
bool whiteQueenSideRookMoved = false;
bool blackQueenSideRookMoved = false;
bool whiteKingSideRookMoved = false;
bool blackKingSideRookMoved = false;
bool whiteToMove = true;
bool blackToMove = false;



    vector<string> whitePieces = {"P","Q", "K", "B", "N", "R"};
    vector<string> blackPieces = {"p","q", "k", "b", "n", "r"};




    while (true) {

        if (programMoveOn < 2) {
            programMove = false;
            simulationWhite = false;
            simulationBlack = false;
        }else {
            programMove = true;
        }
        //piece selection and placement locations
        int dropRight, dropDown;
        if (programMove == false) {
            cout<<"Please select your piece:"<<endl;
            cin >> right >> down;
            if (chessboard[right][down] == "." || right < 1 || (right > 8 && right != 98 & right != 99) || down < 1 || down > 8){
                cout<<"Incorrect piece selection!"<<endl;
                continue;
            }
            cout<<"Select place to drop piece:"<<endl;
            cin>>dropRight>>dropDown;
            if (dropRight == right && dropDown == down){cout<<"Invalid Move!"<<endl;}
        }else {
        if (simulationWhite) {
            right = simulationWhiteKingRight;
            down = simulationWhiteKingDown;
        }else if (simulationBlack) {
            right = simulationBlackKingRight;
            down = simulationBlackKingDown;
        }


        }
        string piece = chessboard[right][down];
        takenPiece = chessboard[dropRight][dropDown];

        if (simulationWhite) {
            piece = "K";
        }else if (simulationBlack) {
            piece = "k";
        }


        if (programMove == false) {
            //whose turn it is and if you're moving a piece of your color
            if (whiteToMove) {
                bool whiteIsMovingAWhitePiece = false;
                for (string whitePiece : whitePieces) {
                    if (whitePiece == chessboard[right][down]) {
                        whiteIsMovingAWhitePiece = true;
                        break;
                    }
                }
                if (whiteIsMovingAWhitePiece == false || piece == ".") {
                    cout<<"Invalid piece selection."<<endl;
                    continue;
                }
            }else if (blackToMove) {
                bool blackIsMovingABlackPiece = false;

                for (string blackPiece : blackPieces) {
                    if (blackPiece == chessboard[right][down]) {
                        blackIsMovingABlackPiece = true;break;
                    }
                }
                if (blackIsMovingABlackPiece == false || piece == ".") {
                    cout<<"Invalid piece selection."<<endl;
                    continue;
                }
            }else {
                cout<<"nope."<<endl;
                return 0;
            }
        }

        if (programMove == false) {
            //make sure you cannot take your own pieces
            if (whiteToMove) {
                bool moveIsAllowed = true;
                for (string whitePiece : whitePieces) {
                    if (whitePiece == takenPiece) {
                        moveIsAllowed = false;
                        break;
                    }
                }
                if (moveIsAllowed == false) {
                    cout<<"Can't take your own pieces."<<endl;
                    chessboard[right][down] = piece;
                    chessboard[dropRight][dropDown] = takenPiece;
                    continue;
                }else{whiteToMove = false;blackToMove = true;}
            }else if (blackToMove) {
                bool moveIsAllowed = true;

                for (string blackPiece : blackPieces) {
                    if (blackPiece == takenPiece) {
                        moveIsAllowed = false;break;
                    }
                }
                if (moveIsAllowed == false) {
                    cout<<"Can't take your own pieces."<<endl;
                    chessboard[right][down] = piece;
                    chessboard[dropRight][dropDown] = takenPiece;
                    continue;
                }else{blackToMove = false;whiteToMove = true;}
            }else {
                cout<<"what the hell did you take??"<<endl;
                return 0;
            }
        }

        //en passant allowment
        if((piece == "p" || piece == "P") && (abs(dropRight - right) == 2) && (right == 2 || right == 7)){
        enPassant = true;
        enPassantStillActive = 2;
            if (piece == "P"){
                enPaassantSqaureRight = dropRight + 1;
                enPassantSqaureDown = dropDown;
            }else{
                enPaassantSqaureRight = dropRight - 1;
                enPassantSqaureDown = dropDown;
            }
        }


        //en passant taking and pawn movement
        if(piece == "P" || piece == "p"){
            //if en passant taking
            if (piece == "P" && enPassant == true && (dropDown == enPassantSqaureDown) && (right == enPaassantSqaureRight + 1 && (down + 1 == enPassantSqaureDown || down - 1 == enPassantSqaureDown)) && right != 7){
                chessboard[right][down] = ".";
                chessboard[dropRight][dropDown] = piece;
                chessboard[enPaassantSqaureRight+1][enPassantSqaureDown] = ".";
            }else if (piece == "p" && enPassant == true && (dropDown == enPassantSqaureDown) && (right == enPaassantSqaureRight - 1 && (down + 1 == enPassantSqaureDown || down - 1 == enPassantSqaureDown)) && right != 2){
                chessboard[right][down] = ".";
                chessboard[dropRight][dropDown] = piece;
                chessboard[enPaassantSqaureRight-1][enPassantSqaureDown] = ".";
            }else{
                //normal pawn moves
                if(piece == "P"){
                    if(((dropRight == right -1 && dropDown == down && chessboard[dropRight][dropDown] == ".") || ((dropDown == down + 1 || dropDown == down - 1)
                        && chessboard[dropRight][dropDown] != "." && dropRight == right -1)) || (dropRight == right-2 && (dropDown == down) && right == 7 && chessboard[right-1][down] == "." && chessboard[dropRight][dropDown] == ".")){
                            chessboard[right][down] = ".";
                            chessboard[dropRight][dropDown] = piece;
                    }else{
                    cout<<"Invalid move! "<<endl;
                        whiteToMove = true; blackToMove = false;
                        continue;
                    }
                }else{
                    if((dropRight == right + 1 && dropDown == down && chessboard[dropRight][dropDown] == ".") || ((dropDown == down + 1 || dropDown == down - 1)
                        &&chessboard[dropRight][dropDown] != "." && dropRight == right +1)  || (dropRight == right+2 && (dropDown == down) && right == 2 && chessboard[right+1][down] == "." && chessboard[dropRight][dropDown] == ".")){
                            chessboard[right][down] = ".";
                            chessboard[dropRight][dropDown] = piece;
                    }else{
                        cout<<"Invalid move! "<<endl;
                        whiteToMove = false; blackToMove = true;
                        continue;
                    }

                }
            }
            //bishops movement
        }else if (piece == "B" || piece == "b") {
            //direction in which the bishop is moving
            int rightStep = 0;
            int downStep = 0;
            if (dropRight - right > 0) {rightStep = 1;}else {rightStep = -1;}
            if (dropDown - down > 0) {downStep = 1;}else {downStep = -1;}

    if (abs(dropRight - right) == abs(dropDown - down)) {
        bool isValidBishopMove = true;

        int i = rightStep + right;
        int j = downStep + down;

        while (i != dropRight && j != dropDown) {

        if (chessboard[i][j] != ".") {
            isValidBishopMove = false;
        }
            i+=rightStep;
            j+=downStep;
        }
        if (isValidBishopMove) {
            chessboard[right][down] = ".";
            chessboard[dropRight][dropDown] = piece;
        }else {
            cout<<"Invalid move! "<<endl;
            if (piece == "B") {
                whiteToMove = true; blackToMove = false;
            }else {
                whiteToMove = false; blackToMove = true;
            }
            continue;
        }
    }else {
        cout<<"Invalid move! "<<endl;
        if (piece == "B") {
            whiteToMove = true; blackToMove = false;
        }else {
            whiteToMove = false; blackToMove = true;
        }
        continue;
    }


//queen movement
        }else if (piece == "Q" || piece == "q") {


            //if a possible diagonal move
            if (abs(dropRight - right) == abs(dropDown - down)) {
                int rightStep = 0;
                int downStep = 0;
                if (dropRight - right > 0) {rightStep = 1;}else {rightStep = -1;}
                if (dropDown - down > 0) {downStep = 1;}else {downStep = -1;}

                bool isValidQueenMove = true;

                int i = rightStep + right;
                int j = downStep + down;

                while (i != dropRight && j != dropDown) {

                    if (chessboard[i][j] != ".") {
                        isValidQueenMove = false;
                    }
                    i+=rightStep;
                    j+=downStep;
                }
                if (isValidQueenMove) {
                    chessboard[right][down] = ".";
                    chessboard[dropRight][dropDown] = piece;
                }else {
                    cout<<"Invalid move! "<<endl;
                    if (piece == "Q") {
                        whiteToMove = true; blackToMove = false;
                    }else {
                        whiteToMove = false; blackToMove = true;
                    }
                    continue;
                }
                //if queen moves horizontally or vertically
            }else if (dropRight == right || dropDown == down) {

                //horizontal move
                if (dropRight == right) {
                    int downStep = 0;
                    if (dropDown - down > 0) {downStep = 1;}else {downStep = -1;}
                    bool isValidQueenMove = true;
                    int j = downStep + down;

                    while (j != dropDown) {
                        if (chessboard[right][j] != ".") {
                            isValidQueenMove = false;
                        }
                        j+=downStep;
                    }
                    if (isValidQueenMove) {
                        chessboard[right][down] = ".";
                        chessboard[dropRight][dropDown] = piece;
                    }else {
                        cout<<"Invalid move! "<<endl;
                        if (piece == "Q") {
                            whiteToMove = true; blackToMove = false;
                        }else {
                            whiteToMove = false; blackToMove = true;
                        }continue;
                    }
                    //vertical move
                }else {
                    int rightStep = 0;

                    if (dropRight - right > 0) {rightStep = 1;}else {rightStep = -1;}

                    bool isValidQueenMove = true;

                    int i = rightStep + right;


                    while (i != dropRight) {
                        if (chessboard[i][down] != ".") {
                            isValidQueenMove = false;
                        }
                        i+=rightStep;
                    }
                    if (isValidQueenMove) {
                        chessboard[right][down] = ".";
                        chessboard[dropRight][dropDown] = piece;
                    }else {
                        cout<<"Invalid move! "<<endl;
                        if (piece == "Q") {
                            whiteToMove = true; blackToMove = false;
                        }else {
                            whiteToMove = false; blackToMove = true;
                        }continue;
                    }
                }
            }else {
                cout<<"Invalid move! "<<endl;
                if (piece == "Q") {
                    whiteToMove = true; blackToMove = false;
                }else {
                    whiteToMove = false; blackToMove = true;
                }continue;
            }

            //rook movement
        }else if (piece == "R" || piece == "r") {

            if (dropRight == right || dropDown == down) {

                //horizontal move
                if (dropRight == right) {
                    int downStep = 0;
                    if (dropDown - down > 0) {downStep = 1;}else {downStep = -1;}
                    bool isValidRookMove = true;
                    int j = downStep + down;

                    while (j != dropDown) {
                        if (chessboard[right][j] != ".") {
                            isValidRookMove = false;
                        }
                        j+=downStep;
                    }
                    if (isValidRookMove) {

                        chessboard[right][down] = ".";
                        chessboard[dropRight][dropDown] = piece;

                    }else {
                        cout<<"Invalid move! "<<endl;
                        if (piece == "R") {
                            whiteToMove = true; blackToMove = false;
                        }else {
                            whiteToMove = false; blackToMove = true;
                        }continue;
                    }
                    //vertical move
                }else {
                    int rightStep = 0;

                    if (dropRight - right > 0) {rightStep = 1;}else {rightStep = -1;}

                    bool isValidRookMove = true;

                    int i = rightStep + right;


                    while (i != dropRight) {
                        if (chessboard[i][down] != ".") {
                            isValidRookMove = false;
                        }
                        i+=rightStep;
                    }
                    if (isValidRookMove) {

                        chessboard[right][down] = ".";
                        chessboard[dropRight][dropDown] = piece;
                    }else {
                        cout<<"Invalid move! "<<endl;
                        if (piece == "R") {
                            whiteToMove = true; blackToMove = false;
                        }else {
                            whiteToMove = false; blackToMove = true;
                        }continue;
                    }
                }
            }else {
                cout<<"Invalid move! "<<endl;
                if (piece == "R") {
                    whiteToMove = true; blackToMove = false;
                }else {
                    whiteToMove = false; blackToMove = true;
                }continue;
            }


        }else if (piece == "N" || piece == "n") {

            //forward and backwards night moves
            if ((dropRight == right + 2 || dropRight == right -2) && (dropDown == down + 1 || dropDown == down - 1)) {
                chessboard[right][down] = ".";
                chessboard[dropRight][dropDown] = piece;
                //left and right night moves
            }else if ((dropRight == right + 1 || dropRight == right -1) && (dropDown == down + 2 || dropDown == down - 2)) {
                chessboard[right][down] = ".";
                chessboard[dropRight][dropDown] = piece;
            }else {
                cout<<"Invalid move! "<<endl;
                if (piece == "N") {
                    whiteToMove = true; blackToMove = false;
                }else {
                    whiteToMove = false; blackToMove = true;
                }continue;
            }


        }else if ((piece == "K" || piece == "k") && !programMove) {
            if (abs(dropRight - right) <= 1 && abs(dropDown - down) <= 1) {
                chessboard[right][down] = ".";
                chessboard[dropRight][dropDown] = piece;
            }


            //castling rules
            //king side castle

            else if (dropRight == right && dropDown == down + 2) {

                if (piece == "K" && isWhiteKingInCheck == false && whiteKingSideCastle && chessboard[8][6] == "." && chessboard[8][7] == "." && whiteKingSideRookMoved == false) {
                    chessboard[8][7] = piece;
                    chessboard[8][5] = ".";
                }else if (piece == "k" && isBlackKingInCheck == false && blackKingSideCastle && chessboard[1][6] == "." && chessboard[1][7] == "." && blackKingSideRookMoved == false) {
                    chessboard[1][7] = piece;
                    chessboard[1][5] = ".";
                }else {
                    cout<<"Invalid move! "<<endl;
                        if (piece == "K") {
                            whiteToMove = true; blackToMove = false;
                        }else if (piece == "k") {
                            whiteToMove = false; blackToMove = true;
                        }
                        continue;
                }
            }
            //queen side castle
            else if (dropRight == right && dropDown == down - 2) {

                if (piece == "K" && isWhiteKingInCheck == false && whiteQueenSideCastle && chessboard[8][3] == "." && chessboard[8][4] == "." && chessboard[8][2] == "." && whiteQueenSideRookMoved == false) {
                    chessboard[8][3] = piece;
                    chessboard[8][5] = ".";
                }else if (piece == "k" && isBlackKingInCheck == false && blackQueenSideCastle && chessboard[1][3] == "." && chessboard[1][4] == "." && chessboard[1][2] == "." && blackQueenSideRookMoved == false) {
                    chessboard[1][3] = piece;
                    chessboard[1][5] = ".";
                }else{
                    cout<<"Invalid move! "<<endl;
                    if (piece == "K") {
                        whiteToMove = true; blackToMove = false;
                    }else if (piece == "k") {
                        whiteToMove = false; blackToMove = true;
                    }
                    continue;}
            }else{
                if (piece == "K") {
                cout<<"Invalid move!"<<endl<<"White to move!"<<endl;
                whiteToMove = true; blackToMove = false;continue;
                }else if (piece == "k") {
                cout<<"Invalid move!"<<endl<<"Black to move!"<<endl;
                whiteToMove = false; blackToMove = true;continue;
                }
            }
        }


 //promotion
            for(int j = 0; j < 9; j++) {
                if (chessboard[8][j] == "p") {
                    cout<<"Select your promotion - q, r, b, n:"<<endl;
                    string promotion; cin>>promotion;
                    if (promotion == "q") {
                        chessboard[8][j] = "q";
                    }else if(promotion == "r"){
                        chessboard[8][j] = "r";
                    }else if(promotion == "b"){
                        chessboard[8][j] = "b";
                    }else{
                        chessboard[8][j] = "n";
                    }
                }else if(chessboard[1][j] == "P"){
                    cout<<"Select your promotion - Q, R, B, N:"<<endl;
                    string promotion; cin>>promotion;
                    if (promotion == "Q") {
                        chessboard[1][j] = "Q";
                    }else if(promotion == "R"){
                        chessboard[1][j] = "R";
                    }else if(promotion == "B"){
                        chessboard[1][j] = "B";
                    }else{
                        chessboard[1][j] = "N";
                    }
                }
            }
			

//king coordinations
        int whiteKingRight = 0;
        int whiteKingDown = 0;
        int blackKingRight = 0;
        int blackKingDown = 0;


            for (int i = 0; i < 9; ++i) {
                for (int j = 0; j < 9; ++j) {
                    if (chessboard[i][j] == "K") {
                        whiteKingRight = i;
                        whiteKingDown = j;
                    }else if (chessboard[i][j] == "k") {
                        blackKingRight = i;
                        blackKingDown = j;
                    }}}

         if (programMove){
            if (simulationWhite){
                whiteKingRight = right;
                whiteKingDown = down;
            }else if(simulationBlack) {
                blackKingRight = right;
                blackKingDown = down;
            }
        }



//is the king in check
        isBlackKingInCheck = false;
        isWhiteKingInCheck = false;
         for (int i = 0; i < 9; ++i) {
             for (int j = 0; j < 9; ++j) {

//pawn checks
             if (chessboard[i][j] == "p") {
                 if (chessboard[i+1][j+1] == "K" || chessboard[i+1][j-1] == "K") {
                     isWhiteKingInCheck = true;
                 }

             }else if(chessboard[i][j] == "P"){
                 if (chessboard[i-1][j-1] == "k" || chessboard[i-1][j+1] == "k") {
                     isBlackKingInCheck = true;
                 }

             }


//bishop checks
             if (chessboard[i][j] == "b") {

                 if (abs(whiteKingRight - i) == abs(whiteKingDown - j)) {
                     int rightStep = 0;
                     int downStep = 0;
                     if (whiteKingRight - i > 0) {rightStep = 1;}else {rightStep = -1;}
                     if (whiteKingDown - j > 0) {downStep = 1;}else {downStep = -1;}



                     bool isValidBishopMove = true;

                     int m = rightStep + i;
                     int n = downStep + j;

                     while (m != whiteKingRight && n!= whiteKingDown) {

                         if (chessboard[m][n] != ".") {
                             isValidBishopMove = false;
                             break;
                         }

                         m+=rightStep;
                         n+=downStep;
                     }
                     if (isValidBishopMove) {
                         isWhiteKingInCheck = true;
                     }
                 }
             }else if(chessboard[i][j] == "B") {

                 if (abs(blackKingRight - i) == abs(blackKingDown - j)) {

                     int rightStep = 0;
                     int downStep = 0;
                     if (blackKingRight - i > 0) {rightStep = 1;}else {rightStep = -1;}
                     if (blackKingDown - j > 0) {downStep = 1;}else {downStep = -1;}


                     bool isValidBishopMove = true;

                     int m = rightStep + i;
                     int n = downStep + j;

                     while (m != blackKingRight && n!= blackKingDown) {

                         if (chessboard[m][n] != ".") {
                             isValidBishopMove = false;
                             break;
                         }

                         m+=rightStep;
                         n+=downStep;
                     }
                     if (isValidBishopMove) {
                         isBlackKingInCheck = true;
                     }
                 }
             }


                 //queen checks
            if (chessboard[i][j] == "Q") {

                //if a possible diagonal white queen check
            if (abs(blackKingRight - i) == abs(blackKingDown - j)) {
                int rightStep = 0;
                int downStep = 0;
                if (blackKingRight - i > 0) {rightStep = 1;}else {rightStep = -1;}
                if (blackKingDown - j > 0) {downStep = 1;}else {downStep = -1;}

                bool isValidQueenMove = true;

                int m = rightStep + i;
                int n = downStep + j;

                while (m != blackKingRight && n!= blackKingDown) {

                    if (chessboard[m][n] != ".") {
                        isValidQueenMove = false;
                        break;
                    }

                    m+=rightStep;
                    n+=downStep;
                }
                if (isValidQueenMove) {
                    isBlackKingInCheck = true;
                }
                //if queen cheks horizontally or vertically
            }else if (blackKingRight == i || blackKingDown == j) {
                //horizontal check
                if (blackKingRight == i) {
                    int downStep = 0;
                    if (blackKingDown - j > 0) {downStep = 1;}else {downStep = -1;}
                    bool isValidQueenMove = true;
                    int n = downStep + j;

                    while (n != blackKingDown) {
                        if (chessboard[i][n] != ".") {
                            isValidQueenMove = false;break;
                        }

                        n+=downStep;
                    }
                    if (isValidQueenMove) {
                        isBlackKingInCheck = true;
                    }
                    //vertical check
                }else {
                    int rightStep = 0;

                    if (blackKingRight - i > 0) {rightStep = 1;}else {rightStep = -1;}

                    bool isValidQueenMove = true;

                    int m = rightStep + i;


                    while (m != blackKingRight) {
                        if (chessboard[m][j] != ".") {
                            isValidQueenMove = false;break;
                        }

                        m+=rightStep;
                    }
                    if (isValidQueenMove) {
                        isBlackKingInCheck = true;

                    }
                }
            }

             }else if(chessboard[i][j] == "q") {

//if a possible diagonal black queen check
            if (abs(whiteKingRight - i) == abs(whiteKingDown - j)) {
                int rightStep = 0;
                int downStep = 0;
                if (whiteKingRight - i > 0) {rightStep = 1;}else {rightStep = -1;}
                if (whiteKingRight - j > 0) {downStep = 1;}else {downStep = -1;}

                bool isValidQueenMove = true;

                int m = rightStep + i;
                int n = downStep + j;

                while (m != whiteKingRight && n!= whiteKingDown) {

                    if (chessboard[m][n] != ".") {
                        isValidQueenMove = false;
                        break;
                    }

                    m+=rightStep;
                    n+=downStep;
                }
                if (isValidQueenMove) {
                    isWhiteKingInCheck = true;
                }
                //if queen cheks horizontally or vertically
            }else if (whiteKingRight == i || whiteKingDown == j) {
                //horizontal check
                if (whiteKingRight == i) {
                    int downStep = 0;
                    if (whiteKingDown - j > 0) {downStep = 1;}else {downStep = -1;}
                    bool isValidQueenMove = true;
                    int n = downStep + j;

                    while (n != whiteKingDown) {
                        if (chessboard[i][n] != ".") {
                            isValidQueenMove = false;break;
                        }

                        n+=downStep;
                    }
                    if (isValidQueenMove) {
                        isWhiteKingInCheck = true;
                    }
                    //vertical check
                }else {
                    int rightStep = 0;

                    if (whiteKingRight - i > 0) {rightStep = 1;}else {rightStep = -1;}

                    bool isValidQueenMove = true;

                    int m = rightStep + i;

                    while (m != whiteKingRight) {
                        if (chessboard[m][j] != ".") {
                            isValidQueenMove = false;break;
                        }

                        m+=rightStep;
                    }
                    if (isValidQueenMove) {
                        isWhiteKingInCheck = true;
                    }
                }
            }
             }

//rook checks
            if (chessboard[i][j] == "R") {

                if (blackKingRight == i || blackKingDown == j) {
                    //horizontal check
                    if (blackKingRight == i) {
                        int downStep = 0;
                        if (blackKingDown - j > 0) {downStep = 1;}else {downStep = -1;}
                        bool isValidRookMove = true;
                        int n = downStep + j;

                        while (n != blackKingDown) {
                            if (chessboard[i][n] != ".") {
                                isValidRookMove = false;break;
                            }

                            n+=downStep;
                        }
                        if (isValidRookMove) {
                            isBlackKingInCheck = true;
                        }
                        //vertical check
                    }else {
                        int rightStep = 0;

                        if (blackKingRight - i > 0) {rightStep = 1;}else {rightStep = -1;}

                        bool isValidRookMove = true;

                        int m = rightStep + i;


                        while (m != blackKingRight) {
                            if (chessboard[m][j] != ".") {
                                isValidRookMove = false;break;
                            }

                            m+=rightStep;
                        }
                        if (isValidRookMove) {
                            isBlackKingInCheck = true;
                        }
                    }
                }

                //black rook checks
            }else if (chessboard[i][j] == "r") {

                //horizontal white rook check
            if (whiteKingRight == i || whiteKingDown == j) {

                if (whiteKingRight == i) {
                    int downStep = 0;
                    if (whiteKingDown - j > 0) {downStep = 1;}else {downStep = -1;}
                    bool isValidRookMove = true;
                    int n = downStep + j;

                    while (n != whiteKingDown) {
                        if (chessboard[i][n] != ".") {
                            isValidRookMove = false;break;
                        }

                        n+=downStep;
                    }
                    if (isValidRookMove) {
                        isWhiteKingInCheck = true;
                    }
                    //vertical white black check
                }else {
                    int rightStep = 0;

                    if (whiteKingRight - i > 0) {rightStep = 1;}else {rightStep = -1;}

                    bool isValidRookMove = true;

                    int m = rightStep + i;

                    while (m != whiteKingRight) {
                        if (chessboard[m][j] != ".") {
                            isValidRookMove = false;break;
                        }

                        m+=rightStep;
                    }
                    if (isValidRookMove) {
                        isWhiteKingInCheck = true;
                    }
                }
            }

            }

            //white knight checks
            if (chessboard[i][j] == "N") {

                //forward and backwards night checks
                if ((blackKingRight == i + 2 || blackKingRight == i -2) && (blackKingDown == j + 1 || blackKingDown == j - 1)) {

                    isBlackKingInCheck = true;
                    //left and right night checks
                }else if ((blackKingRight == i + 1 || blackKingRight == i -1) && (blackKingDown == j + 2 || blackKingDown == j - 2)) {

                    isBlackKingInCheck = true;
                }
                //black night checks
            }else if (chessboard[i][j] == "n") {

                //forward and backwards night checks
                if ((whiteKingRight == i + 2 || whiteKingRight == i -2) && (whiteKingDown == j + 1 || whiteKingDown == j - 1)) {

                   isWhiteKingInCheck = true;
                    //left and right night checks
                }else if ((whiteKingRight == i + 1 || whiteKingRight == i -1) && (whiteKingDown == j + 2 || whiteKingDown == j - 2)) {

                    isWhiteKingInCheck = true;
                }

            }


            // if kings are touching
            if (abs(whiteKingDown - blackKingDown) == 1 && abs(blackKingRight - whiteKingRight) == 1) {
                chessboard[right][down] = piece;
                chessboard[dropRight][dropDown] = takenPiece;
            }

                 //if the opposing king is disallowing castling for whatever reason
                 if (chessboard[i][j] == "K") {
                     for (int m = i-1; m <= i+1; ++m) {
                         for (int n = j-1; n <= j+1 ; ++n) {

                         }
                     }
                 }else if (chessboard[i][j] == "k") {
                     for (int m = i-1; m <= i+1; ++m) {
                         for (int n = j-1; n <= j+1 ; ++n) {

                         }
                     }
                 }
             }
         }



        if (programMove == false) {
            if (isBlackKingInCheck == false) {
                blackKingStillInCheck = false;
                if (blackKingMoved) {
                    blackKingSideCastle = false;
                    blackQueenSideCastle = false;
                }
            }

            if (isWhiteKingInCheck == false) {
                whiteKingStillInCheck = false;
                if (whiteKingMoved) {
                    whiteKingSideCastle = false;
                    whiteQueenSideCastle = false;
                }
            }
        }


		//taking on en passant puts your king in check is illegal
        if (blackToMove && isWhiteKingInCheck && enPassant && piece=="P" && dropDown == enPassantSqaureDown && dropRight == enPaassantSqaureRight) {
            chessboard[right][down] = piece;
            chessboard[enPaassantSqaureRight+1][enPassantSqaureDown] = "p";
            chessboard[dropRight][dropDown] = ".";
            whiteToMove = true;blackToMove = false;
            cout<<"You'll be in check if you play this!"<<endl;continue;
        }else if (whiteToMove && isBlackKingInCheck && enPassant && piece=="p" && dropDown == enPassantSqaureDown && dropRight == enPaassantSqaureRight) {
            chessboard[right][down] = piece;
            chessboard[enPaassantSqaureRight-1][enPassantSqaureDown] = "P";
            chessboard[dropRight][dropDown] = ".";
            whiteToMove = false;blackToMove = true;
            cout<<"You'll be in check if you play this!"<<endl;continue;
        }


        if (blackToMove && isWhiteKingInCheck) {
            chessboard[right][down] = piece;
            chessboard[dropRight][dropDown] = takenPiece;
            whiteToMove = true;blackToMove = false;
            cout<<"You'll be in check if you play this!"<<endl;continue;
        }else if (whiteToMove && isBlackKingInCheck) {
            chessboard[right][down] = piece;
            chessboard[dropRight][dropDown] = takenPiece;
            whiteToMove = false;blackToMove = true;
            cout<<"You'll be in check if you play this!"<<endl;continue;
        }


        //can't give a check if you're currently in check
        if (isBlackKingInCheck && isWhiteKingInCheck){
            chessboard[right][down] = piece;
            chessboard[dropRight][dropDown] = takenPiece;
            whiteToMove = false;blackToMove = true;
            cout<<"You'll be in check if you play this!"<<endl;continue;
        }else if (isBlackKingInCheck && isWhiteKingInCheck){
            chessboard[right][down] = piece;
            chessboard[dropRight][dropDown] = takenPiece;
            whiteToMove = true;blackToMove = false;
            cout<<"You'll be in check if you play this!"<<endl;continue;
        }



// if the passing square during a castle isn't attacked, castling is allowed otherwise the castle is declined
        if (programMove) {
            if (simulationWhite) {
                if (isWhiteKingInCheck) {
                    for (int i = 0; i < 9; i++) {
                        for (int j = 0; j < 9; j++) {
                        chessboard[i][j] = simulationWhiteMatrix [i][j];

                        }}


                    if (simulationWhiteKingSideCastle) {
                        chessboard[8][5] = "K";
                        chessboard[8][6] = ".";
                        chessboard[8][7] = ".";
                        chessboard[8][8] = "R";
                        cout<<"Cannot castle through a check!"<<endl<<"White to move"<<endl;
                        whiteKingSideCastle = true;
                        whiteToMove = true;blackToMove = false;
                        programMoveOn --;
                        isWhiteKingInCheck = false;
                        whiteKingSideRookMoved = false;
                        continue;
                    }else if (simulationWhiteQueenSideCastle) {
                        chessboard[8][5] = "K";
                        chessboard[8][4] = ".";
                        chessboard[8][3] = ".";
                        chessboard[8][1] = "R";
                        cout<<"Cannot castle through a check!"<<endl<<"White to move"<<endl;
                        whiteQueenSideCastle = true;
                        whiteToMove = true;blackToMove = false;
                        programMoveOn --;
                        isWhiteKingInCheck = false;
                        whiteQueenSideRookMoved = false;
                        continue;
                    }
                }else if (isWhiteKingInCheck == false) {
                    for (int i = 0; i < 9; i++) {
                        for (int j = 0; j < 9; j++) {
                            chessboard[i][j] = simulationWhiteMatrix [i][j];

                        }}
                    whiteQueenSideCastle = false;
                    whiteKingSideCastle = false;
                }


            }else if (simulationBlack) {
                if (isBlackKingInCheck) {

                    for (int i = 0; i < 9; i++) {
                        for (int j = 0; j < 9; j++) {
                            chessboard[i][j] = simulationBlackMatrix [i][j];

                        }}


                    if (simulationBlackKingSideCastle) {
                        chessboard[1][5] = "k";
                        chessboard[1][6] = ".";
                        chessboard[1][7] = ".";
                        chessboard[1][8] = "r";
                        cout<<"Cannot castle through a check!"<<endl;
                        blackKingSideCastle = true;
                        whiteToMove = false;blackToMove = true;
                        isBlackKingInCheck = false;
                        blackKingSideRookMoved = false;
                        programMoveOn --;
                        continue;
                    }else if(simulationBlackQueenSideCastle);
                        chessboard[1][5] = "k";
                        chessboard[1][4] = ".";
                        chessboard[1][3] = ".";
                        chessboard[1][1] = "r";
                        cout<<"Cannot castle through a check!"<<endl;
                        blackQueenSideCastle = true;
                        whiteToMove = false;blackToMove = true;
                        programMoveOn --;
                        isBlackKingInCheck = false;
                        blackQueenSideRookMoved = false;
                        continue;
                }else if (isBlackKingInCheck == false) {
                    for (int i = 0; i < 9; i++) {
                        for (int j = 0; j < 9; j++) {
                            chessboard[i][j] = simulationBlackMatrix [i][j];

                        }}
                    blackQueenSideCastle = false;
                    blackKingSideCastle = false;
                }
            }
        }


        if (programMove == false) {
            //if king is in check and after moving is still in check is illegal
            if (isWhiteKingInCheck && whiteKingStillInCheck) {
                chessboard[right][down] = piece;
                chessboard[dropRight][dropDown] = takenPiece;
                cout<<"You're still in check"<<endl;
                //draw board
                for (int i = 0; i < 9; i++) {
                    for (int j = 0; j < 9; j++) {
                        cout << chessboard[i][j] << " ";
                    }
                    cout << endl;
                }
                whiteToMove = true;blackToMove = false;

                continue;
            }else if (isBlackKingInCheck && blackKingStillInCheck) {
                chessboard[right][down] = piece;
                chessboard[dropRight][dropDown] = takenPiece;
                cout<<"You're still in check"<<endl;
                //draw board
                for (int i = 0; i < 9; i++) {
                    for (int j = 0; j < 9; j++) {
                        cout << chessboard[i][j] << " ";
                    }
                    cout << endl;
                }
                blackToMove = true;whiteToMove = false;
                continue;
            }else if(isWhiteKingInCheck && whiteKingStillInCheck == false) {
                cout<<"White King is in check!"<<endl;
                whiteKingStillInCheck = true;
            }else if(isBlackKingInCheck && blackKingStillInCheck == false) {
                cout<<"Black King is in check"<<endl;
                blackKingStillInCheck = true;
            }else if ((piece == "K" || piece == "k")) {
                if (piece == "K" && isWhiteKingInCheck == false && whiteKingStillInCheck == false && abs(dropDown - down) != 2) {
                    whiteKingMoved = true;
                    whiteKingSideCastle = false;
                    whiteQueenSideCastle = false;
                }else if (piece == "k" && isBlackKingInCheck == false && blackKingStillInCheck == false && abs(dropDown - down) != 2) {
                    blackKingMoved = true;
                    blackKingSideCastle = false;
                    blackQueenSideCastle = false;
                }
            }


            //if King castles into check
            if (piece == "K" && dropDown == down + 2 && isWhiteKingInCheck) {
                chessboard[right][down] = piece;
                chessboard[dropRight][dropDown] = takenPiece;
                whiteKingSideCastle = true;
                cout<<"Can't castle into a check!"<<endl;
                whiteToMove = true;blackToMove = false;
            }else if (piece == "K" && dropDown == down - 2 && isWhiteKingInCheck) {
                chessboard[right][down] = piece;
                chessboard[dropRight][dropDown] = takenPiece;
                whiteQueenSideCastle = true;
                cout<<"Can't castle into a check!"<<endl<<endl;
                whiteToMove = true;blackToMove = false;
            }else if (piece == "k" && dropDown == down + 2 && isBlackKingInCheck) {
                chessboard[right][down] = piece;
                chessboard[dropRight][dropDown] = takenPiece;
                blackKingSideCastle = true;
                cout<<"Can't castle into a check!"<<endl;
                whiteToMove = false;blackToMove = true;
            }else if (piece == "k" && dropDown == down - 2 && isBlackKingInCheck) {
                chessboard[right][down] = piece;
                chessboard[dropRight][dropDown] = takenPiece;
                blackQueenSideCastle = true;
                cout<<"Can't castle into a check!"<<endl;
                whiteToMove = false;blackToMove = true;
            }

            //if it enters here the king hasn't castled in check and can move the rook over
            if (piece == "K" && dropDown == down + 2 && isWhiteKingInCheck == false && dropRight == right) {
                chessboard[8][8] = ".";
                chessboard[8][6] = "R";
                for (int i = 0; i < 9; i++) {
                    for (int j = 0; j < 9; j++) {
                        simulationWhiteMatrix[i][j] = chessboard[i][j];}}
                simulationWhiteKingRight = 8;
                simulationWhiteKingDown = 6;
                programMoveOn = 3;
                simulationWhite = true;
                simulationWhiteKingSideCastle = true;
            }else if (piece == "K" && dropDown == down - 2 && isWhiteKingInCheck == false && dropRight == right) {
                chessboard[8][1] = ".";
                chessboard[8][4] = "R";
                for (int i = 0; i < 9; i++) {
                    for (int j = 0; j < 9; j++) {
                        simulationWhiteMatrix[i][j] = chessboard[i][j];}}
                simulationWhiteKingRight = 8;
                simulationWhiteKingDown = 4;
                programMoveOn = 3;
                simulationWhite = true;
                simulationWhiteQueenSideCastle = true;
            }else if (piece == "k" && dropDown == down + 2 && isBlackKingInCheck == false && dropRight == right) {
                chessboard[1][8] = ".";
                chessboard[1][6] = "r";
                for (int i = 0; i < 9; i++) {
                    for (int j = 0; j < 9; j++) {
                        simulationBlackMatrix[i][j] = chessboard[i][j];}}
                simulationBlackKingRight = 1;
                simulationBlackKingDown = 6;
                programMoveOn = 3;
                simulationBlack = true;
                simulationBlackKingSideCastle = true;
            }else if (piece == "k" && dropDown == down- 2 && isBlackKingInCheck == false && dropRight == right) {
                chessboard[1][1] = ".";
                chessboard[1][4] = "r";
                for (int i = 0; i < 9; i++) {
                    for (int j = 0; j < 9; j++) {
                        simulationBlackMatrix[i][j] = chessboard[i][j];}}
                simulationBlackKingRight = 1;
                simulationBlackKingDown = 4;
                programMoveOn = 3;
                simulationBlack = true;
                simulationBlackQueenSideCastle = true;
            }else if ((piece == "K" || piece == "k") && (isWhiteKingInCheck ==false || isBlackKingInCheck ==false) && abs(dropDown - down) == 2 && abs(dropRight - right) != 0) {
            if(piece == "K"){
            cout<<"Incorrect move"<<endl;
            whiteToMove = true;blackToMove = false;
            }else{
            cout<<"Incorrect move"<<endl;
            whiteToMove = false;blackToMove = true;
            }

            }


            //king coordinations
            for (int i = 0; i < 9; ++i) {
                for (int j = 0; j < 9; ++j) {
                    if (chessboard[i][j] == "K") {
                        whiteKingRight = i;
                        whiteKingDown = j;
                    }else if (chessboard[i][j] == "k") {
                        blackKingRight = i;
                        blackKingDown = j;
                    }}}


            //if rook have moved so castle isn't allowed
            if (chessboard[8][8] != "R") {
                whiteKingSideRookMoved = true;}
            if (chessboard[8][1] != "R") {
                whiteQueenSideRookMoved = true;}
            if (chessboard[1][1] != "r") {
                blackQueenSideRookMoved = true;}
            if (chessboard[1][8] != "r") {
                blackKingSideRookMoved = true;}

            if (whiteKingSideRookMoved || whiteQueenSideRookMoved || blackKingSideRookMoved || blackQueenSideRookMoved) {
                if (chessboard[8][8] != "R") {
                    whiteKingSideCastle = false;}
                if (chessboard[8][1] != "R") {
                    whiteQueenSideCastle = false;}
                if (chessboard[1][1] != "r") {
                    blackQueenSideCastle = false;}
                if (chessboard[1][8] != "r") {
                    blackKingSideCastle = false;}
            }

        }

    if (programMove == false) {
        if (isWhiteKingInCheck) {
            simulationIsWhiteKingInCheck = true;
            if (whiteKingStillInCheck) {
                simulationWhiteKingStillInCheck = true;
            }
        }

        if (isBlackKingInCheck) {
            simulationIsBlackKingInCheck = true;
            if (blackKingStillInCheck) {
                simulationBlackKingStillInCheck = true;
            }
        }
    }else if (programMove) {
        isWhiteKingInCheck = simulationIsWhiteKingInCheck;
        isBlackKingInCheck = simulationIsBlackKingInCheck;
        whiteKingStillInCheck = simulationWhiteKingStillInCheck;
        blackKingStillInCheck = simulationBlackKingStillInCheck;
    }

//disable en passant after 1 move
        if(enPassant){
            enPassantStillActive--;

            if(enPassantStillActive < 1){
                enPassant = false;
            }
        }

        if (programMoveOn) {
            programMoveOn--;
        }

        if(programMoveOn < 2) {
            if(whiteToMove) {
                cout<<"White to move"<<endl;
            }else if (blackToMove) {
                cout<<"Black to move"<<endl;
            }
        }


        if (programMoveOn < 2) {
            //draw board
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    cout << chessboard[i][j] << " ";
                }
                cout << endl;
            }
        }
    }


    return 0;
}



