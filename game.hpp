#pragma once
#include "base.hpp"
#include "piece.hpp"

Piece* getPiece(int x, int y);
void changePosition(int x1, int y1, int x2, int y2);
int* parseCommand(string);
void startGame();
void loadGame();
void saveGame();
void roof();
void ceiling();
void floor();
void boardRefresh();


