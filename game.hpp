#pragma once
#include "base.hpp"
#include "piece.hpp"

Piece* getPiece(int, int);
void changePosition(int, int, int, int);
int* parseCommand(string);
string checkMove(int, int, int, int);
string getTurn();
void changeTurn();
void startGame();
void loadGame();
void saveGame();
void roof();
void ceiling();
void floor();
void boardRefresh();


