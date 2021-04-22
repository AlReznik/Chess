#pragma once
#include "base.hpp"
#include "piece.hpp"
#include "chessboard.hpp"

class Game
{
public:
    Game();
    static void start();
    static void loadGame();
    static void saveGame();
    static void startGame();
    static Piece* getPiece(int, int);
    static string getTurn();
    static void changeTurn();
    static void moveKing(int, int);
    static bool checkBoard(int, int, int, int);
    static void changePosition(int, int, int, int);
    static void saveMove(int, int, int, int);
    static void cleanBoard();
    static bool simulateMove(int, int, int, int);
    static bool checkUnderAttack(string);
    static bool checkMate(string);
};






