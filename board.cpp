#include "base.hpp"
#include "board.hpp"
#include "king.hpp"
#include "queen.hpp"
#include "pawn.hpp"
#include "rook.hpp"
#include "knight.hpp"
#include "bishop.hpp"

/*! \file board.cpp
* @brief class Board definition file
*/

Board::Board()
{
    for(int y = 0; y<8; y++)
    {
        for (int x = 0; x<8; x++)
        {
            board[y][x]=0;
        }
    }
}
// Return piece object located at square address
/**
 * @param x X-coordinate of the board
 * @param y Y-coordinate of the board
 * @return pointer to Piece object
 */
Piece* Board::getPiece(int x, int y)
{
    return board[y][x];
}

/**
 * @param x X-coordinate of the board
 * @param y Y-coordinate of the board
 * @param color the color of the piece
 * @param type the type of the piece
 */
void Board::setPiece(int x, int y, string color, int type)
{
    switch (type)
    {
    case 1:
        board[y][x] = new Bishop(color);
        break;
    case 2:
        board[y][x] = new King(color);
        break;
    case 3:
        board[y][x] = new Knight(color);
        break;
    case 4:
        board[y][x] = new Pawn(color);
        break;
    case 5:
        board[y][x] = new Queen(color);
        break;
    case 6:
        board[y][x] = new Rook(color);
        break;       
    }
    
}

/**
 * @param x1 X-coordinate the piece is been moved from
 * @param y1 Y-coordinate the piece is been moved from
 * @param x2 X-coordinate the piece is been moved to
 * @param y2 Y-coordinate the piece is been moved to
 */
void Board::changePosition(int x1, int y1, int x2, int y2)
{
    // case 1 pawn captures another pawn en passant
    if (getPiece(x1,y1)->getType() == "pawn" && getPiece(x2,y1) != 0 && getPiece(x2,y1)->getEnPassant() == 1)
    {
        board[y2][x2] = board[y1][x1];
        board[y1][x1] = 0;
        delete board[y1][x2];
        board[y1][x2] = 0;
    }
    // case 2 pawn promotion
    else if (getPiece(x1,y1)->getType() == "pawn" && (y2 == 0 || y2 == 7))
    {
        if (getPiece(x2,y2) != 0)
            delete board[y2][x2];
        board[y1][x1] = 0;
    }
    // case 3 white king left castling
    else if (getPiece(x1,y1)->getType() == "king" && y1 == 0 && x1 == 4 && x2 == 2)
    {
        board[y2][x2] = board[y1][x1];
        board[y1][x1] = 0;
        board[0][3] = board[0][0];
        board[0][0] = 0;
    }
    // case 4 white king right castling
    else if (getPiece(x1,y1)->getType() == "king" && y1 == 0 && x1 == 4 && x2 == 6)
    {
        board[y2][x2] = board[y1][x1];
        board[y1][x1] = 0;
        board[0][5] = board[0][7];
        board[0][7] = 0;
    }
    // case 5 black king left castling
    else if (getPiece(x1,y1)->getType() == "king" && y1 == 7 && x1 == 4 && x2 == 2)
    {
        board[y2][x2] = board[y1][x1];
        board[y1][x1] = 0;
        board[7][3] = board[7][0];
        board[7][0] = 0;
    }
    // case 6 black king right castling
    else if (getPiece(x1,y1)->getType() == "king" && y1 == 7 && x1 == 4 && x2 == 6)
    {
        board[y2][x2] = board[y1][x1];
        board[y1][x1] = 0;
        board[7][5] = board[7][7];
        board[7][7] = 0;
    }
    // case 6 simple move
    else
    {
        // with capturing
        if (getPiece(x2,y2) != 0)
            delete board[y2][x2];
        board[y2][x2] = board[y1][x1];
        board[y1][x1] = 0;
    }
}

/**
 * @return current position on the board
 */
array <array <Piece*,8>,8> Board::getBoard()
{
    return board;
}

bool Board::nextMove(int x1, int y1, int x2, int y2, string input, UI ui)
{
    if(getPiece(x1,y1)->checkMove(x1,y1,x2,y2,board,check))
    {
        movePiece(x1,y1,x2,y2,input,ui);
        if (checkUnderAttack(getTurn()))
        {
            check = 1;
            ui.sendMessage("Check! \xF0\x9F\x98\x83");
            if (checkMate(getTurn()))
            {
                string winner = getTurn() == "white" ? "black" : "white";
                ui.sendMessage("Mate! "+ winner + " has won! \xF0\x9F\x98\x83");
                ui.refreshBoard(board);
                exit(0);
            }
        }
        else
        {
            check = 0;
        }
        if (checkMate(getTurn()))
        {
            ui.refreshBoard(board);
            ui.sendMessage("Stablemate! \xF0\x9F\x98\x83");
            exit(0);
        }
        return 1;
    }
    else
    {
        ui.sendMessage("This move isn't allowed \xF0\x9F\x98\x95");
        return 0;
    }
             
}

string Board::getTurn()
{
    return turn == 0 ? "white" : "black";
}

void Board::changeTurn()
{
    turn = !turn;
}

/**
 * @param x1 X-coordinate the piece is been moved from
 * @param y1 Y-coordinate the piece is been moved from
 * @param x2 X-coordinate the piece is been moved to
 * @param y2 Y-coordinate the piece is been moved to
 * @param str string representation of the move
 * @param ui user interface object
 */
void Board::movePiece(int x1, int y1, int x2, int y2, string str, UI ui)
{
    // lambdas for getting color, type and symbol of the piece in beginning or ending position of the move
    // used for shorter notation
    auto c1 = [this,x1,y1](){return this->getPiece(x1,y1)->getColor();}; auto c2 = [this,x2,y2](){return this->getPiece(x2,y2)->getColor();};
    auto t1 = [this,x1,y1](){return this->getPiece(x1,y1)->getType();}; auto t2 = [this,x2,y2](){return this->getPiece(x2,y2)->getType();};
    auto s1 = [this,x1,y1](){return this->getPiece(x1,y1)->getSymbol();}; auto s2 = [this,x2,y2](){return this->getPiece(x2,y2)->getSymbol();};
    string from = str.substr(0,2), to = str.substr(3,2), sm1 = "! \xF0\x9F\x98\x83", sm2 = " \xF0\x9F\x99\x81";

    // case 1 message after capturing
    if (getPiece(x2,y2))
    {
        ui.sendMessage(c1() + " " + t1() + " " + s1() + "  " + from + " is capturing " + c2() + " " + t2() + " " + s2() + "  " + to + " " + sm1);
        ui.sendMessage (c2() + " " + t2() + " is out of the game" + sm2);
    }
    // case 2 message after castling
    else if (t1() == "king" && (x2-x1) > 1)
    {
        ui.sendMessage(c1() + " " + t1() + " " + s1() + "  " + from + " is making castling " + to + " " + sm1);
    }
    // case 3 message after capturing en passant
    else if  (t1() == "pawn" && getPiece(x2,y2) == 0 && getPiece(x2,y1) != 0 && getPiece(x2,y1)->getEnPassant() == 1)
    {
        ui.sendMessage(c1() + " "+ t1() + " " + s1() + "  " + from + " is capturing " + getPiece(x2,y1)->getColor() + " " + getPiece(x2,y1)->getType() + " " +
                getPiece(x2,y1)->getSymbol() + "  " + to + " en passant" + sm1);
        ui.sendMessage (getPiece(x2,y1)->getColor() + " " + getPiece(x2,y1)->getType() + " is out of the game \xF0\x9F\x99\x81");
    }
    // case 4 message after simple move
    else
    {
        ui.sendMessage(c1() + " " + t1() + " " + s1() + "  " + from + " is moving " + to + " " + sm1);
    }
    // move of the pawn that can be captured en passant
    if ( ((abs(y2-y1) == 2 && getPiece(x1+1,y2) != 0 && getPiece(x1+1,y2)->getType() == "pawn" && getPiece(x1+1,y2)->getColor() != c1()) ||
            (abs(y2-y1) == 2 && getPiece(x1-1,y2) != 0 && getPiece(x1-1,y2)->getType() == "pawn" && getPiece(x1-1,y2)->getColor() != c1())) && t1() == "pawn" )
    {
        ui.sendMessage("En passant!");
        getPiece(x1,y1)->setEnPassant();
    }
    // save last king's position
    if (t1() == "king") {moveKing(x2,y2);}
    // set the piece has been moved
    getPiece(x1,y1)->setMoved();
    // pawn promotion
    if (t1() == "pawn" && (y2 == 0 || y2 == 7))
    {
        changePosition(x1,y1,x2,y2);
        promotePawn(x2,y2,ui);
    }
    else
    {
        changePosition(x1,y1,x2,y2);
    }
    // change turn
    changeTurn();
}

/**
 * @param x X-coordinate the king is been moved to
 * @param y Y-coordinate the king is been moved to
 */
void Board::moveKing(int x, int y)
{
    if (getTurn() == "white")
        whiteKing[0] = x, whiteKing[1] = y;
    else
        blackKing[0] = x, blackKing[1] = y;
}
/**
 * @param x1 X-coordinate the piece is been moved from
 * @param y1 Y-coordinate the piece is been moved from
 * @param x2 X-coordinate the piece is been moved to
 * @param y2 Y-coordinate the piece is been moved to
 * @param ui user interface object
 * @return true if validation is successful
 */
bool Board::checkBoard(int x1, int y1, int x2, int y2, UI ui)
{
    // attempt to start from empty square
    if (getPiece(x1,y1) == 0)
    {
        ui.sendMessage("There are no pieceses here! \xF0\x9F\x98\x95");
        return 0;
    }
    // attempt to move other player's piece
    else if (getPiece(x1,y1)->getColor() != getTurn())
    {
        ui.sendMessage("It's "+ getTurn() +"'s turn to move now! \xF0\x9F\x98\x95");
        return 0;
    }
    // attempt to capture own piece
    else if (getPiece(x2,y2) != 0 && getPiece(x2,y2)->getColor() == getTurn())
    {
        ui.sendMessage("You can't capture own piece! \xF0\x9F\x98\x95");
        return 0;
    }
    else return 1;
}
/**
 * @param x1 X-coordinate the piece is been moved from
 * @param y1 Y-coordinate the piece is been moved from
 * @param x2 X-coordinate the piece is been moved to
 * @param y2 Y-coordinate the piece is been moved to
 * @return true if the king is under attack after simulation
 */
bool Board::simulateMove(int x1, int y1, int x2, int y2)
{
    array <array <Piece*,8>,8> sboard = getBoard(); //!< saved board copy before simulation
    bool isKing = getPiece(x1,y1)->getType() == "king";
    // lambda for deleting all piece objects after simulation
    auto clean = [this]()
    {
        for (int y = 0; y < 8; y++)
            for (int x = 0; x < 8; x++)
                if (this->getPiece(x,y) != 0) delete this->getPiece(x,y);
    };
    // create copies of all piece objects on the second board
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if (getPiece(x,y) != 0)
            {
                string color = getPiece(x,y)->getColor();
                if (getPiece(x,y)->getType() == "pawn")
                {
                    sboard[y][x] = new Pawn(color);
                    if (getPiece(x,y)->getEnPassant()) sboard[y][x]->setEnPassant();
                    if (getPiece(x,y)->getIsMoved()) sboard[y][x]->setMoved();
                }
                if (getPiece(x,y)->getType() == "bishop")
                    sboard[y][x] = new Bishop(color);
                if (getPiece(x,y)->getType() == "knight")
                    sboard[y][x] = new Knight(color);
                if (getPiece(x,y)->getType() == "rook")
                {
                    sboard[y][x] = new Rook(color);
                    if (getPiece(x,y)->getIsMoved()) sboard[y][x]->setMoved();
                }                 
                if (getPiece(x,y)->getType() == "queen")
                    sboard[y][x] = new Queen(color);
                if (getPiece(x,y)->getType() == "king")
                {
                    sboard[y][x] = new King(color);
                    if (getPiece(x,y)->getIsMoved()) sboard[y][x]->setMoved();
                }               
            }
        }
    }
    changePosition(x1,y1,x2,y2);
    if (isKing) moveKing(x2,y2);
    // after simulation clean the board
    // replace the board by saved copy of initial position
    // replace last king's position
    if (checkUnderAttack(getTurn()))
    {
        clean();
        board = sboard;
        if (isKing) moveKing(x1,y1);
        return 1;
    }
    else
    {
        clean();
        board = sboard;
        if (isKing) moveKing(x1,y1);
        return 0;
    }
}

/**
 * Test all other player's pieces on the board if any of them can check king
 * 
 * @param turn turn to move
 */
bool Board::checkUnderAttack(string turn)
{
    int x2;
    int y2;
    if (getTurn() == "white")
    {
        x2 = whiteKing[0];
        y2 = whiteKing[1];
    }
    else
    {
        x2 = blackKing[0];
        y2 = blackKing[1];
    }
    for (int y1 = 0; y1 < 8; y1++)
    {
        for (int x1 = 0; x1 < 8; x1++)
        {
            if (getPiece(x1,y1) != 0 && getPiece(x1,y1)->getColor() != getTurn() && getPiece(x1,y1)->checkMove(x1,y1,x2,y2,getBoard(),check))
            {
                return 1;
            }
        }
    }
    return 0;
}

/**
 * Test all own pieces if any of them can make a move freeing king out of being under attack
 * 
 * @param turn turn to move
 */
bool Board::checkMate(string turn)
{
    for (int y1 = 0; y1 < 8; y1++)
    {
        for (int x1 = 0; x1 < 8; x1++)
        {
            if (getPiece(x1,y1) != 0 && getPiece(x1,y1)->getColor() == getTurn())
            {
                for (int y2 = 0; y2 < 8; y2++)
                {
                    for (int x2 = 0; x2 < 8; x2++)
                    {
                        if (!(getPiece(x2,y2) != 0 && getPiece(x2,y2)->getColor() == getTurn()) && getPiece(x1,y1)->checkMove(x1,y1,x2,y2,getBoard(),check) && !simulateMove(x1,y1,x2,y2))
                        {
                            return 0;
                        }
                    }
                }

            }
        }
    }
    return 1;
}

void Board::compMove(UI ui)
{
    map<int,string> dict = {{0,"a"},{1,"b"},{2,"c"},{3,"d"},{4,"e"},{5,"f"},{6,"g"},{7,"h"}}; //!< map for converting move to string notation
    vector<array<int,4>> moves; //!< container for keeping all possible moves at current position
    int x1, y1, x2, y2; //!< coordinates of future move
    string move; //!< move in string notation
    // find all possible moves at current position
    for (int y3 = 0; y3 < 8; y3++)
    {
        for (int x3 = 0; x3 < 8; x3++)
        {
            if (getPiece(x3,y3) != 0 && getPiece(x3,y3)->getColor() == getTurn())
            {
                for (int y4 = 0; y4 < 8; y4++)
                {
                    for (int x4 = 0; x4 < 8; x4++)
                    {
                        if ((getPiece(x4,y4) == 0 && getPiece(x3,y3)->checkMove(x3,y3,x4,y4,board,check) && !simulateMove(x3,y3,x4,y4)) ||
                            (getPiece(x4,y4) != 0 && getPiece(x4,y4)->getColor() != getTurn() && getPiece(x3,y3)->checkMove(x3,y3,x4,y4,board,check) && !simulateMove(x3,y3,x4,y4)))
                        {
                            array<int,4> temp = {x3,y3,x4,y4};
                            moves.push_back(temp);
                        }
                    }
                }
            }
        }
    }   
    // select random move
    ui.sendMessage("I have "+ to_string(moves.size()) + " moves in this position");
    srand((unsigned) time(0));
    int r = (rand() % moves.size());
    ui.sendMessage("I have chosen move number #" + to_string(r+1));

    x1 = moves[r][0], y1 = moves[r][1], x2 = moves[r][2], y2 = moves[r][3];
    move = dict[x1] + to_string(y1+1) + "-" + dict[x2] + to_string(y2+1);
    movePiece(x1,y1,x2,y2,move,ui);
    if (checkUnderAttack(getTurn()))
    {
        check = 1;
        ui.sendMessage("Check! \xF0\x9F\x98\x83");
        if (checkMate(getTurn()))
        {
            string winner = getTurn() == "white" ? "black" : "white";
            ui.sendMessage("Mate! "+ winner + " has won! \xF0\x9F\x98\x83");
            ui.refreshBoard(board);
            exit(0);
        }
    }
    else
    {
        check = 0;
    }
    if (checkMate(getTurn()))
    {
        ui.refreshBoard(board);
        ui.sendMessage("Stablemate! \xF0\x9F\x98\x83");
        exit(0);
    }
    ui.refreshBoard(getBoard());
    ui.sendMessage(getTurn() + ", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
}

void Board::promotePawn(int x, int y, UI ui)
{
    if (compgame)
    {
        setPiece(x,y,getTurn(),5);
    }
    else
    {
        string piece;
        while (true)
        {
            ui.sendMessage(getTurn() + ", choose one of of the pieces to promote your pawn:");
            ui.sendMessage("Bishop (B), Knight (K), Rook (R) or Queen (Q)");
            piece = ui.getInput();
            if (piece == "b")
            {
                setPiece(x,y,getTurn(),1);
                break;
            }
            else if (piece == "k")
            {
                setPiece(x,y,getTurn(),3);
                break;
            }
            else if (piece == "r")
            {
                setPiece(x,y,getTurn(),6);
                break;
            }
            else if (piece == "q")
            {
                setPiece(x,y,getTurn(),5);
                break;
            }
            else
            {
                ui.sendMessage("Command nod recognized! \xF0\x9F\x98\x95");
            }
        }
        ui.sendMessage (getTurn() + " pawn is replaced by "+ getPiece(x,y)->getType() +"! \xF0\x9F\x98\x83");
    }
}