#pragma once
#include "base.hpp"
#include "piece.hpp"
#include "game.hpp"

class Queen : public Piece
{
public:
    Queen(string);
    bool movePiece(int, int, int, int, string) override;
    string getSymbol() override;
    bool checkMove(int, int, int, int) override;
};