#include "king.hpp"

King::King(string color, string position)
: Piece("king", color, position, false){}

void King::movePiece(int x1, int y1, int x2, int y2)
{
    if (getPiece(x1,y1)->getType() == "king")
    {
        changePosition(x1,y1,x2,y2);
        cout << this->getSymbol()<< "  King is moving! \xF0\x9F\x98\x83\n";
    }
    else
    {
        cout << "Not a king!\n";
    }
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
