#pragma once
#include "base.hpp"
#include "piece.hpp"
#include "game.hpp"

class Rook : public Piece
{
public:
    Rook(string, string);
    void movePiece(int, int, int, int) override;
    string getSymbol() override;
};