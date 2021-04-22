#pragma once
#include "base.hpp"
#include "piece.hpp"
#include "game.hpp"

class Pawn : public Piece
{
public:
    Pawn(string);
    bool movePiece(int, int, int, int, string) override;
    string getSymbol() override;
    bool checkMove(int, int, int, int) override;
};