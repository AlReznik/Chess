#include "base.hpp"
#include "piece.hpp"
#include "game.hpp"

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    sendMessage("Welcome to Console Chess App! \xF0\x9F\x98\x83");
    sendMessage("Do you want to load saved game(L), start new game(N) or quit(Q)?");
    string start;
    while (true)
    {
        start = getInput();
        if (start == "l")
        {
            loadGame();
            boardRefresh();
            sendMessage(getTurn() + ", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
            break;
        }
        else if (start == "q")
        {
            sendMessage("Goodbye! \xF0\x9F\x98\x83");
            return 0;
        }
        else if (start == "n")
        {
            startGame();
            boardRefresh();
            sendMessage(getTurn() + ", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
            break;
        }
        else
        {
            sendMessage("Command nod recognized! \xF0\x9F\x98\x95");
            sendMessage("Do you want to load saved game(L) or start new game(N)?");
        }
    }
    string input;
    while (true)
    {
        input = getInput();
        if (checkInput(input))
        {
            int x1 = parseCommand(input)[0]; int y1 = parseCommand(input)[1];
            int x2 = parseCommand(input)[2]; int y2 = parseCommand(input)[3];
            if (checkBoard(x1,y1,x2,y2))
            {
                if (simulateMove(x1,y1,x2,y2))
                {
                    sendMessage("This move isn't allowed, your king will be under attack ! \xF0\x9F\x98\x95");
                    sendMessage(getTurn() + ", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
                }
                else
                {
                    getPiece(x1,y1)->movePiece(x1,y1,x2,y2,input);
                    if (checkUnderAttack(getTurn()))
                    {
                        sendMessage("Check! \xF0\x9F\x98\x83");
                        if (checkMate(getTurn()))
                        {
                            string winner = getTurn() == "white" ? "black" : "white";
                            sendMessage("Mate! "+ winner + " has won! \xF0\x9F\x98\x83");
                            boardRefresh();
                            break;
                        }
                    }
                    if (checkMate(getTurn()))
                    {
                        string winner = getTurn() == "white" ? "white" : "black";
                        boardRefresh();
                        sendMessage("Stablemate! \xF0\x9F\x98\x83");
                        break;
                    }
                    boardRefresh();
                    sendMessage(getTurn() + ", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
                }

            }
            else
            {
                sendMessage(getTurn() + ", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
            }   
        }
        else if (input == "s")
        {
            saveGame();
            return 0;
        }
        else if (input == "q")
        {
            sendMessage("Goodbye! \xF0\x9F\x98\x83");
            return 0;
        }
        else
        {
            sendMessage("Command nod recognized! \xF0\x9F\x98\x95");
            sendMessage(getTurn() + ", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
        }
    }  
    return 0;
}