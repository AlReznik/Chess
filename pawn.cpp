#include "pawn.hpp"

/*! \file pawn.cpp
* @brief class Pawn definition file
*/

/**
 * Constructor for creating objects of class Pawn
 * 
 * @param color describes color of the pawn
 */
Pawn::Pawn(string color)
: Piece("pawn", color, false, false){}

/**
 * @return pawn symbol, white or black, in UTF8 encoding
 */
string Pawn::getSymbol()
{
    if (this->color == "white")
        return "\xE2\x99\x9F";
    else
        return "\xE2\x99\x99";
}

/**
 * @param x1 X-coordinate the piece is been moved from
 * @param y1 Y-coordinate the piece is been moved from
 * @param x2 X-coordinate the piece is been moved to
 * @param y2 Y-coordinate the piece is been moved to
 * @param board pass current position on the board
 * @param check pass value if the king is being checked
 * @return true if validation is successful
 */
bool Pawn::checkMove(int x1, int y1, int x2, int y2, array <array <Piece*,8>,8> board, bool check)
{
    if (this->getColor() == "white" &&
        ((x2 == x1 && board[y2][x2] == 0 && ((y2-y1 == 2 && board[y1+1][x1] == 0  && this->getIsMoved() == 0) || y2-y1 == 1)) ||
            (abs(x2-x1) == 1 && y2-y1 == 1 &&  (board[y2][x2] != 0 ||  (board[y1][x2] != 0 && board[y1][x2]->getEnPassant() == 1)) )) )
    {
        return 1;
    }
    else if (this->getColor() == "black" &&
        ((x2 == x1 && board[y2][x2] == 0 && ((y1-y2 == 2 && board[y1-1][x1] == 0  && this->getIsMoved() == 0) || y1-y2 == 1)) ||
            (abs(x2-x1) == 1 && y1-y2 == 1 &&  (board[y2][x2] != 0 ||  (board[y1][x2] != 0 && board[y1][x2]->getEnPassant() == 1)) )) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}