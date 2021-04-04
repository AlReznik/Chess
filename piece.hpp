#pragma once
#include "base.hpp"

class Piece
{
public:
    Piece(string, string, string, bool);
    string getType();
    string getPosition();
    void setPosition(string position);
    virtual void movePiece(int, int, int, int) = 0;
    virtual string getSymbol() = 0; 
protected:
    string type;
    string color;
    string position;
    bool isMoved;
};