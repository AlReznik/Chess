#pragma once
#include "base.hpp"

class Chessboard
{
public:
    Chessboard();
    static void boardRefresh();
    static void sendMessage(string);
    static string getInput();
    static bool checkInput(string);
    static int* parseCommand(string);
    static void roof();
    static void ceiling();
    static void floor();
};

