#include "rook.hpp"

Rook::Rook(string color, string position)
: Piece("rook", color, position, false){}

bool Rook::movePiece(int x1, int y1, int x2, int y2, string str)
{
    if (checkMove(x1,y1,x2,y2))
    {
        changePosition(x1,y1,x2,y2);
        sendMessage(getTurn() + " "+ this->getType() +" " + this->getSymbol() + "  is moving " + str + " ! \xF0\x9F\x98\x83");
        changeTurn();
        this->isMoved = true;
        cout << isMoved << endl;
        return 1;
    }
    else
    {
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
bool Rook::checkMove(int x1, int y1, int x2, int y2)
{
    if(x2-x1 <= 2)
    {
        return 1;
    }
    else
    {
        sendMessage("This move isn't allowed \xF0\x9F\x98\x95");
        return 0;
    }
}