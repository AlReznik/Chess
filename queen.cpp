#include "queen.hpp"

Queen::Queen(string color, string position)
: Piece("queen", color, position, false){}

void Queen::movePiece(int x1, int y1, int x2, int y2)
{
/*     cout << this->type << endl;
    cout << this->color << endl;
    cout << this->position << endl;
    cout << this->symbol << endl;
    cout << this->isMoved << endl; */
}

string Queen::getSymbol()
{
    if(this->color == "white")
    {
        return "\xE2\x99\x9B";
    }
    else
    {
        return "\xE2\x99\x95";
    }
}