#pragma once
#include "base.hpp"
#include "piece.hpp"

class Bishop : public Piece
{
public:
    Bishop(string, string);
    void movePiece(int, int, int, int) override;
    string getSymbol() override;
};