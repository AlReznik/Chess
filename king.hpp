#pragma once
#include "base.hpp"
#include "piece.hpp"
#include "game.hpp"
#include "chessboard.hpp"

class King : public Piece
{
public:
    King(string);
    bool movePiece(int, int, int, int, string) override;
    string getSymbol() override;
    bool checkMove(int, int, int, int) override;
};