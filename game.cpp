#include "base.hpp"
#include "game.hpp"
#include "board.hpp"

/*! \file game.cpp
* @brief class Game definition file
*/

/**
 * Construct an object of class Game; 
 * Run introduction; 
 * After selection run chosen game mode
 */
Game::Game()
{
    intro();
    playGame();
}

void Game::intro()
{
    string start;
    while (true)
    {
        start = ui.getInput();
        if (start == "l")
        {
            b.compgame = 0;
            loadGame();
            ui.refreshBoard(b.getBoard());
            ui.sendMessage(b.getTurn() + ", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
            break;
        }
        else if (start == "q")
        {
            ui.sendMessage("Goodbye! \xF0\x9F\x98\x83");
            exit(0);
        }
        else if (start == "n")
        {
            b.compgame = 0;
            startGame();
            ui.refreshBoard(b.getBoard());
            ui.sendMessage(b.getTurn() + ", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
            break;
        }
        else if (start == "c")
        {
            b.compgame = 1;
            startGame();
            ui.refreshBoard(b.getBoard());
            ui.sendMessage("You play white pieces, make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
            break;
        }
        else
        {
            ui.sendMessage("Command nod recognized! \xF0\x9F\x98\x95");
            ui.sendMessage("Do you want to load saved game(L) or start new game(N)?");
        }
    }
}

void Game::playGame()
{
    string input;
    while (true)
    {
        if (!b.compgame || (!b.turn && b.compgame))
        {
            input = ui.getInput();
            if (ui.checkInput(input))
            {
                int x1 = ui.parseCommand(input)[0]; int y1 = ui.parseCommand(input)[1];
                int x2 = ui.parseCommand(input)[2]; int y2 = ui.parseCommand(input)[3];
                if (b.checkBoard(x1,y1,x2,y2, ui))
                {
                    if (b.simulateMove(x1,y1,x2,y2))
                    {
                        ui.sendMessage("This move isn't allowed, your king will be under attack ! \xF0\x9F\x98\x95");
                        ui.sendMessage(b.getTurn() + ", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
                    }
                    else
                    {
                        if (b.nextMove(x1,y1,x2,y2,input,ui))
                        {
                        ui.refreshBoard(b.getBoard());
                        ui.sendMessage(b.getTurn() + ", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
                        // save last move
                        history.push_back(to_string(x1) + to_string(y1) + to_string(x2) + to_string(y2));
                        }
                    }
                }
                else
                {
                    ui.sendMessage(b.getTurn() + ", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
                }   
            }
            else if (input == "s")
            {
                saveGame();
                exit(0);
            }
            else if (input == "q")
            {
                ui.sendMessage("Goodbye! \xF0\x9F\x98\x83");
                exit(0);
            }
            else
            {
                ui.sendMessage("Command nod recognized! \xF0\x9F\x98\x95");
                ui.sendMessage(b.getTurn() + ", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
            }
        }
        else
        {
            b.compMove(ui);
        }
    }  
}

void Game::loadGame()
{
    string line;
    ifstream in("history.txt");
    if (in.is_open())
    {
        while (getline(in, line))
        {
            history.push_back(line);
        }
    }
    in.close();
    startGame();
    for (string i : history)
    {
        int x1 = stoi(i.substr(0,1)), y1 = stoi(i.substr(1,1));
        int x2 = stoi(i.substr(2,1)), y2 = stoi(i.substr(3,1));
        b.changePosition(x1,y1,x2,y2);
        b.changeTurn();
    }
    ui.sendMessage("Game is loaded! \xF0\x9F\x98\x83");
}

void Game::saveGame()
{
    ofstream out;
    out.open("history.txt");
    if (out.is_open())
    {
        for (string move : history)
        {
            out << move << endl;
        }
    }
    out.close();
    ui.sendMessage("Game is saved! \xF0\x9F\x98\x83");
}

void Game::startGame()
{
    b.setPiece(0,0,"white",6); b.setPiece(7,0,"white",6);
    b.setPiece(1,0,"white",3); b.setPiece(6,0,"white",3);  
    b.setPiece(2,0,"white",1); b.setPiece(5,0,"white",1);
    b.setPiece(3,0,"white",5); b.setPiece(4,0,"white",2);  
    b.setPiece(0,7,"black",6); b.setPiece(7,7,"black",6);
    b.setPiece(1,7,"black",3); b.setPiece(6,7,"black",3);   
    b.setPiece(2,7,"black",1); b.setPiece(5,7,"black",1);
    b.setPiece(3,7,"black",5); b.setPiece(4,7,"black",2);
    for(int i = 0; i<8; i++) {b.setPiece(i,1,"white",4);}
    for(int i = 0; i<8; i++) {b.setPiece(i,6,"black",4);}
    b.turn = 0;
    b.whiteKing[0] = 4, b.whiteKing[1] = 0;
    b.blackKing[0] = 4, b.blackKing[1] = 7;
}
