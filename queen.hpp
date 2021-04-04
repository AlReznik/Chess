#pragma once
#include "base.hpp"
#include "piece.hpp"

class Queen : public Piece
{
public:
    Queen(string, string);
    void movePiece(int, int, int, int) override;
    string getSymbol() override;
};