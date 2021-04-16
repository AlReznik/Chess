#include "king.hpp"

King::King(string color)
: Piece("king", color, false){}

bool King::movePiece(int x1, int y1, int x2, int y2, string str)
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
        else if (abs(x2-x1) > 1)
        {
            sendMessage(this->getColor() + " " + this->getType() + " " + this->getSymbol() + "  " + str.substr(0,2) + " is making castling " 
                + str.substr(3,2) + " ! \xF0\x9F\x98\x83");
        }
        else
        {
            sendMessage(this->getColor() + " " + this->getType() + " " + this->getSymbol() + "  " + str.substr(0,2) + " is moving " 
                + str.substr(3,2) + " ! \xF0\x9F\x98\x83");
        }
        changePosition(x1,y1,x2,y2);
        moveKing(x2,y2);
        changeTurn();
        setMoved();
        saveMove(x1,y1,x2,y2);
        return 1;
    }
    else
    {
        sendMessage("This move isn't allowed \xF0\x9F\x98\x95");
        return 0;
    }
}
string King::getSymbol()
{
    if(this->color == "white")
        return "\xE2\x99\x9A";
    else
        return "\xE2\x99\x94";
}
bool King::checkMove(int x1, int y1, int x2, int y2)
{
    if (abs(x2-x1) <= 1 && abs(y2-y1) <= 1)
    {
        return 1;
    }
    else if( ( (y2 == 0 && ((x2 == 2 && getPiece(1,0) == 0 && getPiece(2,0) == 0 && getPiece(3,0) == 0 && getPiece(0,0) != 0 && getPiece(0,0)->getIsMoved() == 0) ||
                            (x2 == 6 && getPiece(5,0) == 0 && getPiece(6,0) == 0 &&                       getPiece(7,0) != 0 && getPiece(7,0)->getIsMoved() == 0)) ) || 
                (y2 == 7 && ((x2 == 2 && getPiece(1,7) == 0 && getPiece(2,7) == 0 && getPiece(3,7) == 0 && getPiece(0,7) != 0 && getPiece(0,7)->getIsMoved() == 0) ||
                            (x2 == 6 && getPiece(5,7) == 0 && getPiece(6,7) == 0 &&                        getPiece(7,7) != 0 && getPiece(7,7)->getIsMoved() == 0))) ) && 
            this->getIsMoved() == 0 && !checkUnderAttack(getTurn()) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
