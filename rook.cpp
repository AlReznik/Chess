#include "rook.hpp"

/*! \file rook.cpp
* @brief class Rook definition file
*/

/**
 * Constructor for creating objects of class Rook
 * 
 * @param color describes color of the rook
 */
Rook::Rook(string color)
: Piece("rook", color, false){}

/**
 * @return rook symbol, white or black, in UTF8 encoding
 */
string Rook::getSymbol()
{
    if (this->color == "white")
        return "\xE2\x99\x9C";
    else
        return "\xE2\x99\x96";
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
bool Rook::checkMove(int x1, int y1, int x2, int y2, array <array <Piece*,8>,8> board, bool check)
{
    int xDir = (x2-x1) > 0 ? 1 : -1;
    int yDir = (y2-y1) > 0 ? 1 : -1;
    if (x2 == x1)
    {
        for (int i = 1; i < abs(y2-y1); ++i)
        {
            if  (board[y1 + i * yDir][x1] != 0)
            {
                return 0;
            }
        }
        return 1;
    }
    else if (y2 == y1)
    {
        for (int i = 1; i < abs(x2-x1); ++i)
        {
            if  (board[y1][x1 + i * xDir] != 0)
            {
                return 0;
            }
        }
        return 1;
    }
    else
    {
        return 0;
    }
}