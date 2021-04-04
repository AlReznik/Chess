#include "knight.hpp"

Knight::Knight(string color, string position)
: Piece("knight", color, position, false){}

void Knight::movePiece(int x1, int y1, int x2, int y2)
{
/*     cout << this->type << endl;
    cout << this->color << endl;
    cout << this->position << endl;
    cout << this->symbol << endl;
    cout << this->isMoved << endl; */
}

string Knight::getSymbol()
{
    if(this->color == "white")
    {
        return "\xE2\x99\x9E";
    }
    else
    {
        return "\xE2\x99\x98";
    }
}