#pragma once
#include "base.hpp"

class Piece
{
public:
    Piece(string, string, string, bool);
    string getType();
    string getPosition();
    string getColor();
    void setPosition(string position);
    virtual bool movePiece(int, int, int, int, string) = 0;
    virtual string getSymbol() = 0;
    virtual bool checkMove(int, int, int, int) = 0; 
protected:
    string type;
    string color;
    string position;
    bool isMoved;
};