#include "pawn.hpp"

Pawn::Pawn(string color, string position)
: Piece("pawn", color, position, false){}

bool Pawn::movePiece(int x1, int y1, int x2, int y2)
{
    if (checkMove(x1,y1,x2,y2) == "allowed")
    {
        changePosition(x1,y1,x2,y2);
        cout << getTurn() <<" pawn " << this->getSymbol() << "  is moving " << x1<< y1 << x2 << y2 <<" ! \xF0\x9F\x98\x83\n";
        changeTurn();
        return 1;
    }
    else
    {
        cout << "Not a pawn!\n";
        return 0;
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