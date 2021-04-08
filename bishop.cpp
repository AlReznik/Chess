#include "bishop.hpp"

Bishop::Bishop(string color, string position)
: Piece("bishop", color, position, false){}

bool Bishop::movePiece(int x1, int y1, int x2, int y2)
{
    if (getPiece(x1,y1)->getType() == "bishop")
    {
        changePosition(x1,y1,x2,y2);
        cout << this->getSymbol()<< "  Bishop is moving! \xF0\x9F\x98\x83\n";
        changeTurn();
        return 1;
    }
    else
    {
        cout << "Not a bishop!\n";
        return 0;
    }
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