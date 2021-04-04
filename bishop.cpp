#include "bishop.hpp"

Bishop::Bishop(string color, string position)
: Piece("bishop", color, position, false){}

void Bishop::movePiece(int x1, int y1, int x2, int y2)
{
/*     cout << this->type << endl;
    cout << this->color << endl;
    cout << this->position << endl;
    cout << this->symbol << endl;
    cout << this->isMoved << endl; */
}

string Bishop::getSymbol()
{
    if(this->color == "white")
    {
        return "\xE2\x99\x9D";
    }
    else
    {
        return "\xE2\x99\x97";
    }
}