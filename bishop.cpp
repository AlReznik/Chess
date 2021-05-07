#include "bishop.hpp"

/*! \file bishop.cpp
* @brief class Bishop definition file
*/

/**
 * Constructor for creating objects of class Bishop
 * 
 * @param color describes color of the bishop
 */
Bishop::Bishop(string color)
: Piece("bishop", color, false){}

/**
 * @return bishop symbol, white or black, in UTF8 encoding
 */
string Bishop::getSymbol()
{
    if (this->getColor() == "white")
        return "\xE2\x99\x9D";
    else
        return "\xE2\x99\x97";
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
bool Bishop::checkMove(int x1, int y1, int x2, int y2, array <array <Piece*,8>,8> board, bool check)
{
    if (abs(x2-x1) == abs(y2-y1))
    {
        int xDir = (x2-x1) > 0 ? 1 : -1;
        int yDir = (y2-y1) > 0 ? 1 : -1;
        for (int i = 1; i < abs(x2-x1); ++i)
        {
            if  (board[y1 + i * yDir][x1 + i * xDir])
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