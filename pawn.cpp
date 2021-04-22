#include "pawn.hpp"

Pawn::Pawn(string color)
: Piece("pawn", color, false, false){}

extern Chessboard ch;
extern Game g;
bool Pawn::movePiece(int x1, int y1, int x2, int y2, string str)
{
    if (checkMove(x1,y1,x2,y2))
    {
        if  (g.getPiece(x2,y2) != 0)
        {
            ch.sendMessage(this->getColor() + " " + this->getType() + " " + this->getSymbol() + "  " + str.substr(0,2) + " is capturing " + 
                g.getPiece(x2,y2)->getColor() + " " + g.getPiece(x2,y2)->getType() + " " +
                    g.getPiece(x2,y2)->getSymbol() + "  " + str.substr(3,2) + " ! \xF0\x9F\x98\x83");
            ch.sendMessage(g.getPiece(x2,y2)->getColor() + " " + g.getPiece(x2,y2)->getType() + " is out of the game \xF0\x9F\x99\x81");
        }
        else if  (g.getPiece(x2,y2) == 0 && g.getPiece(x2,y1) != 0 && g.getPiece(x2,y1)->getEnPassant() == 1)
        {
            ch.sendMessage(this->getColor() + " "+ this->getType() + " " + this->getSymbol() + "  " + str.substr(0,2) + " is capturing " + 
                g.getPiece(x2,y1)->getColor() + " " + g.getPiece(x2,y1)->getType() + " " +
                    g.getPiece(x2,y1)->getSymbol() + "  " + str.substr(3,2) + " en passant! \xF0\x9F\x98\x83");
            ch.sendMessage (g.getPiece(x2,y1)->getColor() + " " + g.getPiece(x2,y1)->getType() + " is out of the game \xF0\x9F\x99\x81");
        }
        else
        {
            ch.sendMessage(this->getColor() + " "+ this->getType() + " " + this->getSymbol() + "  " + str.substr(0,2) + " is moving " 
                + str.substr(3,2) + " ! \xF0\x9F\x98\x83");
        }
        g.changePosition(x1,y1,x2,y2);       
        g.changeTurn();
        setMoved();
        if ((abs(y2-y1) == 2 && g.getPiece(x1+1,y2) != 0 && g.getPiece(x1+1,y2)->getType() == "pawn" && g.getPiece(x1+1,y2)->getColor() != this->color) ||
            (abs(y2-y1) == 2 && g.getPiece(x1-1,y2) != 0 && g.getPiece(x1-1,y2)->getType() == "pawn" && g.getPiece(x1-1,y2)->getColor() != this->color))
        {
            ch.sendMessage("En passant!");
            setEnPassant();
        }
        g.saveMove(x1,y1,x2,y2);
        return 1;
    }
    else
    {
        ch.sendMessage("This move isn't allowed \xF0\x9F\x98\x95");
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
        ((x2 == x1 && g.getPiece(x2,y2) == 0 && ((y2-y1 == 2 && g.getPiece(x1,y1+1) == 0  && this->getIsMoved() == 0) || y2-y1 == 1)) ||
            (abs(x2-x1) == 1 && y2-y1 == 1 &&  (g.getPiece(x2,y2) != 0 ||  (g.getPiece(x2,y1) != 0 && g.getPiece(x2,y1)->getEnPassant() == 1)) )) )
    {
        return 1;
    }
    else if (this->getColor() == "black" &&
        ((x2 == x1 && g.getPiece(x2,y2) == 0 && ((y1-y2 == 2 && g.getPiece(x1,y1-1) == 0  && this->getIsMoved() == 0) || y1-y2 == 1)) ||
            (abs(x2-x1) == 1 && y1-y2 == 1 &&  (g.getPiece(x2,y2) != 0 ||  (g.getPiece(x2,y1) != 0 && g.getPiece(x2,y1)->getEnPassant() == 1)) )) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}