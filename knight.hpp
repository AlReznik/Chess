#pragma once
#include "base.hpp"
#include "piece.hpp"
#include "game.hpp"

class Knight : public Piece
{
public:
    Knight(string, string);
    bool movePiece(int, int, int, int) override;
    string getSymbol() override;
};