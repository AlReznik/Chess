#include "pawn.hpp"

Pawn::Pawn(string color, string position)
: Piece("pawn", color, position, false){}

void Pawn::movePiece(int x1, int y1, int x2, int y2)
{
    cout << "Rook is moving"<< endl;
}

string Pawn::getSymbol()
{
    if(this->color == "white")
    {
        return "\xE2\x99\x9F";
    }
    else
    {
        return "\xE2\x99\x99";
    }
}