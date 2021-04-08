#include "rook.hpp"

Rook::Rook(string color, string position)
: Piece("rook", color, position, false){}

bool Rook::movePiece(int x1, int y1, int x2, int y2)
{
    if (getPiece(x1,y1)->getType() == "rook")
    {
        changePosition(x1,y1,x2,y2);
        cout << this->getSymbol()<< "  Rook is moving! \xF0\x9F\x98\x83\n";
        changeTurn();
        return 1;
    }
    else
    {
        cout << "Not a rook!\n";
        return 0;
    }

}

string Rook::getSymbol()
{
    if(this->color == "white")
    {
        return "\xE2\x99\x9C";
    }
    else
    {
        return "\xE2\x99\x96";
    }
}