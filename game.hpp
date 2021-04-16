#pragma once
#include "base.hpp"
#include "piece.hpp"
#include "chessboard.hpp"

bool checkInput(string input);
void loadGame();
void saveGame();
void startGame();
int* parseCommand(string);
Piece* getPiece(int, int);
string getTurn();
void changeTurn();
void moveKing(int, int);
bool checkBoard(int, int, int, int);
void changePosition(int, int, int, int);
void saveMove(int, int, int, int);
void cleanBoard();
bool simulateMove(int, int, int, int);
bool checkUnderAttack(string);
bool checkMate(string);





