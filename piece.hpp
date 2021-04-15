#pragma once
#include "base.hpp"

class Piece
{
public:
    Piece(string, string, bool, bool);
    Piece(string, string, bool);
    string getType();
    string getColor();
    bool getEnPassant();
    virtual bool movePiece(int, int, int, int, string) = 0;
    virtual string getSymbol() = 0;
    virtual bool checkMove(int, int, int, int) = 0; 
protected:
    string type;
    string color;
    bool isMoved;
    bool isEnPassant;
};