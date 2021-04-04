#pragma once
#include "base.hpp"
#include "piece.hpp"

Piece* getPiece(int x, int y);
void changePosition(int x1, int y1, int x2, int y2);
int* parseString(string);
void StartGame();
void LoadGame();
void SaveGame();
void roof();
void ceiling();
void floor();
void BoardRefresh();


