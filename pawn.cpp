#include "pawn.hpp"

Pawn::Pawn(string color)
: Piece("pawn", color, false, false){}

bool Pawn::movePiece(int x1, int y1, int x2, int y2, string str)
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
        else if (getPiece(x2,y2) == 0 && getPiece(x2,y1) != 0 && getPiece(x2,y1)->getEnPassant() == 1)
        {
            sendMessage(this->getColor() + " "+ this->getType() + " " + this->getSymbol() + "  " + str.substr(0,2) + " is capturing " + 
                getPiece(x2,y1)->getColor() + " " + getPiece(x2,y1)->getType() + " " +
                    getPiece(x2,y1)->getSymbol() + "  " + str.substr(3,2) + " en passant! \xF0\x9F\x98\x83");
            sendMessage("in");
            sendMessage(getPiece(x2,y1)->getColor() + " " + getPiece(x2,y1)->getType() + " is out of the game \xF0\x9F\x99\x81");
            sendMessage("out");
        }
        else
        {
            sendMessage(this->getColor() + " "+ this->getType() + " " + this->getSymbol() + "  " + str.substr(0,2) + " is moving " 
                + str.substr(3,2) + " ! \xF0\x9F\x98\x83");
        }
        changePosition(x1,y1,x2,y2);       
        changeTurn();
        setMoved();
        if ((abs(y2-y1) == 2 && getPiece(x1+1,y2) != 0 && getPiece(x1+1,y2)->getType() == "pawn" && getPiece(x1+1,y2)->getColor() != this->color) ||
            (abs(y2-y1) == 2 && getPiece(x1-1,y2) != 0 && getPiece(x1-1,y2)->getType() == "pawn" && getPiece(x1-1,y2)->getColor() != this->color))
        {
            sendMessage("En passant!");
            setEnPassant();
        }
        saveMove(x1,y1,x2,y2);
        return 1;
    }
    else
    {
        sendMessage("This move isn't allowed \xF0\x9F\x98\x95");
        return 0;
    }
}
string Pawn::getSymbol()
{
    if (this->color == "white")
        return "\xE2\x99\x9F";
    else
        return "\xE2\x99\x99";
}
bool Pawn::checkMove(int x1, int y1, int x2, int y2)
{
    if (this->getColor() == "white" &&
        ((x2 == x1 && getPiece(x2,y2) == 0 && ((y2-y1 == 2 && getPiece(x1,y1+1) == 0  && this->getIsMoved() == 0) || y2-y1 == 1)) ||
            (abs(x2-x1) == 1 && y2-y1 == 1 && (getPiece(x2,y2) != 0 || (getPiece(x2,y1) != 0 && getPiece(x2,y1)->getEnPassant() == 1)) )) )
    {
        return 1;
    }
    else if (this->getColor() == "black" &&
        ((x2 == x1 && getPiece(x2,y2) == 0 && ((y1-y2 == 2 && getPiece(x1,y1-1) == 0  && this->getIsMoved() == 0) || y1-y2 == 1)) ||
            (abs(x2-x1) == 1 && y1-y2 == 1 && (getPiece(x2,y2) != 0 || (getPiece(x2,y1) != 0 && getPiece(x2,y1)->getEnPassant() == 1)) )) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}