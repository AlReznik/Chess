#pragma once
#include "base.hpp"
#include "piece.hpp"
#include "game.hpp"

class King : public Piece
{
public:
    King(string, string);
    void movePiece(int, int, int, int) override;
    string getSymbol() override;
};