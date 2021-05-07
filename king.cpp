#include "king.hpp"

/*! \file king.cpp
* @brief class King definition file
*/

/**
 * Constructor for creating objects of class King
 * 
 * @param color describes color of the king
 */
King::King(string color)
: Piece("king", color, false){}

/**
 * @return king symbol, white or black, in UTF8 encoding
 */
string King::getSymbol()
{
    if(this->color == "white")
        return "\xE2\x99\x9A";
    else
        return "\xE2\x99\x94";
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
bool King::checkMove(int x1, int y1, int x2, int y2, array <array <Piece*,8>,8> board, bool check)
{
    if (abs(x2-x1) <= 1 && abs(y2-y1) <= 1)
    {
        return 1;
    }
    else if( ( (y2 == 0 && ((x2 == 2 && board[0][1] == 0 && board[0][2] == 0 && board[0][3] == 0 && board[0][0] != 0 && board[0][0]->getIsMoved() == 0) ||
                            (x2 == 6 && board[0][5] == 0 && board[0][6] == 0 &&                       board[0][7] != 0 && board[0][7]->getIsMoved() == 0)) ) || 
                (y2 == 7 && ((x2 == 2 && board[7][1] == 0 && board[7][2] == 0 && board[7][3] == 0 && board[7][0] != 0 && board[7][0]->getIsMoved() == 0) ||
                            (x2 == 6 && board[7][5] == 0 && board[7][6] == 0 &&                        board[7][7] != 0 && board[7][7]->getIsMoved() == 0))) ) && 
            this->getIsMoved() == 0 && !check )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
