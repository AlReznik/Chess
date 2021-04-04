#pragma once
#include "base.hpp"
#include "piece.hpp"

class Pawn : public Piece
{
public:
    Pawn(string, string);
    void movePiece(int, int, int, int) override;
    string getSymbol() override;
};