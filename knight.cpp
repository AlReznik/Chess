#include "knight.hpp"

/*! \file knight.cpp
* @brief class Knight definition file
*/

/**
 * Constructor for creating objects of class Knight
 * 
 * @param color describes color of the knight
 */
Knight::Knight(string color)
: Piece("knight", color, false){}

/**
 * @return knight symbol, white or black, in UTF8 encoding
 */
string Knight::getSymbol()
{
    if (this->color == "white")
        return "\xE2\x99\x9E";
    else
        return "\xE2\x99\x98";
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
bool Knight::checkMove(int x1, int y1, int x2, int y2, array <array <Piece*,8>,8> board, bool check)
{
    if ((abs(x2-x1) == 2 && abs(y2-y1) == 1) || (abs(x2-x1) == 1 && abs(y2-y1) == 2))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}