#include "queen.hpp"

Queen::Queen(string color, string position)
: Piece("queen", color, position, false){}

void Queen::movePiece(int x1, int y1, int x2, int y2)
{
    if (getPiece(x1,y1)->getType() == "queen")
    {
        changePosition(x1,y1,x2,y2);
        cout << this->getSymbol()<< "  Queen is moving! \xF0\x9F\x98\x83\n";
    }
    else
    {
        cout << "Not a queen!\n";
    }
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