#pragma once
#include "base.hpp"
#include "piece.hpp"
#include "game.hpp"

class Bishop : public Piece
{
public:
    Bishop(string, string);
    bool movePiece(int, int, int, int) override;
    string getSymbol() override;
};