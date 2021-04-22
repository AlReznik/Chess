#include "bishop.hpp"

Bishop::Bishop(string color)
: Piece("bishop", color, false){}

extern Chessboard ch;
extern Game g;
bool Bishop::movePiece(int x1, int y1, int x2, int y2, string str)
{
    if (checkMove(x1,y1,x2,y2))
    {
        if (g.getPiece(x2,y2) != 0)
        {
            ch.sendMessage(this->getColor() + " " + this->getType() + " " + this->getSymbol() + "  " + str.substr(0,2) + " is capturing " + 
                g.getPiece(x2,y2)->getColor() + " " + g.getPiece(x2,y2)->getType() + " " +
                    g.getPiece(x2,y2)->getSymbol() + "  " + str.substr(3,2) + " ! \xF0\x9F\x98\x83");
            ch.sendMessage (g.getPiece(x2,y2)->getColor() + " " + g.getPiece(x2,y2)->getType() + " is out of the game \xF0\x9F\x99\x81");
        }
        else
        {
            ch.sendMessage(this->getColor() + " " + this->getType() + " " + this->getSymbol() + "  " + str.substr(0,2) + " is moving " 
                + str.substr(3,2) + " ! \xF0\x9F\x98\x83");
        }
        g.changePosition(x1,y1,x2,y2);       
        g.changeTurn();
        g.saveMove(x1,y1,x2,y2);
        return 1;
    }
    else
    {
        ch.sendMessage("This move isn't allowed \xF0\x9F\x98\x95");
        return 0;
    }
}
string Bishop::getSymbol()
{
    if (this->getColor() == "white")
        return "\xE2\x99\x9D";
    else
        return "\xE2\x99\x97";
}
bool Bishop::checkMove(int x1, int y1, int x2, int y2)
{
    if (abs(x2-x1) == abs(y2-y1))
    {
        int xDir = (x2-x1) > 0 ? 1 : -1;
        int yDir = (y2-y1) > 0 ? 1 : -1;
        for (int i = 1; i < abs(x2-x1); ++i)
        {
            if  (g.getPiece(x1 + i * xDir, y1 + i * yDir) != 0)
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