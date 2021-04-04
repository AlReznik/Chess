#include "king.hpp"

King::King(string color, string position)
: Piece("king", color, position, false){}

void King::movePiece(int x1, int y1, int x2, int y2)
{
/*     cout << this->type << endl;
    cout << this->color << endl;
    cout << this->position << endl;
    cout << this->symbol << endl;
    cout << this->isMoved << endl; */
}

string King::getSymbol()
{
    if(this->color == "white")
    {
        return "\xE2\x99\x9A";
    }
    else
    {
        return "\xE2\x99\x94";
    }
}
