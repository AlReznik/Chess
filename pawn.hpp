#pragma once
#include "base.hpp"
#include "piece.hpp"
#include "game.hpp"

class Pawn : public Piece
{
public:
    Pawn(string, string);
    bool movePiece(int, int, int, int) override;
    string getSymbol() override;
};