#include "pawn.hpp"

Pawn::Pawn(string color, string position)
: Piece("pawn", color, position, false){}

void Pawn::movePiece(int x1, int y1, int x2, int y2)
{
    if (getPiece(x1,y1)->getType() == "pawn")
    {
        changePosition(x1,y1,x2,y2);
        cout << this->getSymbol()<< "  Pawn is moving! \xF0\x9F\x98\x83\n";
    }
    else
    {
        cout << "Not a pawn!\n";
    }
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