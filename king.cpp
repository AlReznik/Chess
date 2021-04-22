#include "king.hpp"

King::King(string color)
: Piece("king", color, false){}

extern Chessboard ch;
extern Game g;
bool King::movePiece(int x1, int y1, int x2, int y2, string str)
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
        else if (abs(x2-x1) > 1)
        {
            ch.sendMessage(this->getColor() + " " + this->getType() + " " + this->getSymbol() + "  " + str.substr(0,2) + " is making castling " 
                + str.substr(3,2) + " ! \xF0\x9F\x98\x83");
        }
        else
        {
            ch.sendMessage(this->getColor() + " " + this->getType() + " " + this->getSymbol() + "  " + str.substr(0,2) + " is moving " 
                + str.substr(3,2) + " ! \xF0\x9F\x98\x83");
        }
        g.changePosition(x1,y1,x2,y2);
        g.moveKing(x2,y2);
        g.changeTurn();
        setMoved();
        g.saveMove(x1,y1,x2,y2);
        return 1;
    }
    else
    {
        ch.sendMessage("This move isn't allowed \xF0\x9F\x98\x95");
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
    else if( ( (y2 == 0 && ((x2 == 2 && g.getPiece(1,0) == 0 && g.getPiece(2,0) == 0 && g.getPiece(3,0) == 0 && g.getPiece(0,0) != 0 && g.getPiece(0,0)->getIsMoved() == 0) ||
                            (x2 == 6 && g.getPiece(5,0) == 0 && g.getPiece(6,0) == 0 &&                       g.getPiece(7,0) != 0 && g.getPiece(7,0)->getIsMoved() == 0)) ) || 
                (y2 == 7 && ((x2 == 2 && g.getPiece(1,7) == 0 && g.getPiece(2,7) == 0 && g.getPiece(3,7) == 0 && g.getPiece(0,7) != 0 && g.getPiece(0,7)->getIsMoved() == 0) ||
                            (x2 == 6 && g.getPiece(5,7) == 0 && g.getPiece(6,7) == 0 &&                        g.getPiece(7,7) != 0 && g.getPiece(7,7)->getIsMoved() == 0))) ) && 
            this->getIsMoved() == 0 && !g.checkUnderAttack (g.getTurn()) )
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
