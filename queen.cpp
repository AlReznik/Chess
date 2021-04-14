#include "queen.hpp"

Queen::Queen(string color)
: Piece("queen", color, false){}

bool Queen::movePiece(int x1, int y1, int x2, int y2, string str)
{
    if (checkMove(x1,y1,x2,y2))
    {
        if (getPiece(x2,y2) != 0)
        {
            sendMessage(this->getColor() + " " + this->getType() + " " + this->getSymbol() + "  " + str.substr(0,2) + " is capturing " + 
                getPiece(x2,y2)->getColor() + " " + getPiece(x2,y2)->getType() + " " +
                    getPiece(x2,y2)->getSymbol() + "  " + str.substr(3,2) + " ! \xF0\x9F\x98\x83");
            sendMessage(getPiece(x2,y2)->getColor() + " " + getPiece(x2,y2)->getType() + " is out of the game \xF0\x9F\x99\x81");
        }
        else
        {
            sendMessage(this->getColor() + " " + this->getType() + " " + this->getSymbol() + "  " + str.substr(0,2) + " is moving " 
                + str.substr(3,2) + " ! \xF0\x9F\x98\x83");
        }
        changePosition(x1,y1,x2,y2);       
        changeTurn();
        this->isMoved = true;
        saveMove(x1,y1,x2,y2);
        return 1;
    }
    else
    {
        sendMessage("This move isn't allowed \xF0\x9F\x98\x95");
        return 0;
    }
}
string Queen::getSymbol()
{
    if (this->color == "white")
        return "\xE2\x99\x9B";
    else
        return "\xE2\x99\x95";
}
bool Queen::checkMove(int x1, int y1, int x2, int y2)
{
    int xDir = (x2-x1) > 0 ? 1 : -1;
    int yDir = (y2-y1) > 0 ? 1 : -1;
    if (x2 == x1)
    {
        for (int i = 1; i < abs(y2-y1); ++i)
        {
            if (getPiece(x1, y1 + i * yDir) != 0)
            {
                return 0;
            }
        }
        return 1;
    }
    else if (y2 == y1)
    {
        for (int i = 1; i < abs(x2-x1); ++i)
        {
            if (getPiece(x1 + i * xDir, y1) != 0)
            {
                return 0;
            }
        }
        return 1;
    }
    else if (abs(x2-x1) == abs(y2-y1))
    {
        for (int i = 1; i < abs(x2-x1); ++i)
        {
            if (getPiece(x1 + i * xDir, y1 + i * yDir) != 0)
            {
                return 0;
            }
        }
        return 1;
    }
    else
    {
        return 0;
    }
}