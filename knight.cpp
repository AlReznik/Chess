#include "knight.hpp"

Knight::Knight(string color, string position)
: Piece("knight", color, position, false){}

void Knight::movePiece(int x1, int y1, int x2, int y2)
{
    if (getPiece(x1,y1)->getType() == "knight")
    {
        changePosition(x1,y1,x2,y2);
        cout << this->getSymbol()<< "  Knight is moving! \xF0\x9F\x98\x83\n";
    }
    else
    {
        cout << "Not a knight!\n";
    }
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