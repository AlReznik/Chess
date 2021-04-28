#include "base.hpp"
#include "game.hpp"
#include "king.hpp"
#include "queen.hpp"
#include "pawn.hpp"
#include "rook.hpp"
#include "knight.hpp"
#include "bishop.hpp"

array <array <Piece*,8>,8> board;
vector <string> history;
bool turn;
bool game;
int whiteKing[2];
int blackKing[2];
Chessboard ch;

Game::Game()
{
    start();
    game ? playCompGame() : playGame();
}
// Initial stage
void Game::start()
{
    string start;
    while (true)
    {
        start = ch.getInput();
        if (start == "l")
        {
            loadGame();
            ch.boardRefresh();
            ch.sendMessage(getTurn() + ", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
            break;
        }
        else if (start == "q")
        {
            ch.sendMessage("Goodbye! \xF0\x9F\x98\x83");
            exit(0);
        }
        else if (start == "n")
        {
            startGame();
            ch.boardRefresh();
            ch.sendMessage(getTurn() + ", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
            break;
        }
        else if (start == "c")
        {
            game = 1;
            startGame();
            ch.boardRefresh();
            ch.sendMessage("You play white pieces, make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
            break;
        }
        else
        {
            ch.sendMessage("Command nod recognized! \xF0\x9F\x98\x95");
            ch.sendMessage("Do you want to load saved game(L) or start new game(N)?");
        }
    }
}
// Play game with computer
void Game::playGame()
{
    string input;
    while (true)
    {
        input = ch.getInput();
        if (ch.checkInput(input))
        {
            int x1 = ch.parseCommand(input)[0]; int y1 = ch.parseCommand(input)[1];
            int x2 = ch.parseCommand(input)[2]; int y2 = ch.parseCommand(input)[3];
            if (checkBoard(x1,y1,x2,y2))
            {
                if (simulateMove(x1,y1,x2,y2))
                {
                    ch.sendMessage("This move isn't allowed, your king will be under attack ! \xF0\x9F\x98\x95");
                    ch.sendMessage(getTurn() + ", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
                }
                else
                {
                    getPiece(x1,y1)->movePiece(x1,y1,x2,y2,input);
                    if (checkUnderAttack(getTurn()))
                    {
                        ch.sendMessage("Check! \xF0\x9F\x98\x83");
                        if (checkMate(getTurn()))
                        {
                            string winner = getTurn() == "white" ? "black" : "white";
                            ch.sendMessage("Mate! "+ winner + " has won! \xF0\x9F\x98\x83");
                            ch.boardRefresh();
                            break;
                        }
                    }
                    if (checkMate(getTurn()))
                    {
                        string winner = getTurn() == "white" ? "white" : "black";
                        ch.boardRefresh();
                        ch.sendMessage("Stablemate! \xF0\x9F\x98\x83");
                        break;
                    }
                    ch.boardRefresh();
                    ch.sendMessage(getTurn() + ", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
                }

            }
            else
            {
                ch.sendMessage(getTurn() + ", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
            }   
        }
        else if (input == "s")
        {
            saveGame();
            exit(0);
        }
        else if (input == "q")
        {
            ch.sendMessage("Goodbye! \xF0\x9F\x98\x83");
            exit(0);
        }
        else
        {
            ch.sendMessage("Command nod recognized! \xF0\x9F\x98\x95");
            ch.sendMessage(getTurn() + ", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
        }
    }  
}
// Play game with computer
void Game::playCompGame()
{
    string input;
    while (true)
    {
        if (!turn)
        {
            input = ch.getInput();
            if (ch.checkInput(input))
            {
                int x1 = ch.parseCommand(input)[0]; int y1 = ch.parseCommand(input)[1];
                int x2 = ch.parseCommand(input)[2]; int y2 = ch.parseCommand(input)[3];
                if (checkBoard(x1,y1,x2,y2))
                {
                    if (simulateMove(x1,y1,x2,y2))
                    {
                        ch.sendMessage("This move isn't allowed, your king will be under attack ! \xF0\x9F\x98\x95");
                        ch.sendMessage(getTurn() + ", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
                    }
                    else
                    {
                        getPiece(x1,y1)->movePiece(x1,y1,x2,y2,input);
                        if (checkUnderAttack(getTurn()))
                        {
                            ch.sendMessage("Check! \xF0\x9F\x98\x83");
                            if (checkMate(getTurn()))
                            {
                                string winner = getTurn() == "white" ? "black" : "white";
                                ch.sendMessage("Mate! "+ winner + " has won! \xF0\x9F\x98\x83");
                                ch.boardRefresh();
                                break;
                            }
                        }
                        if (checkMate(getTurn()))
                        {
                            string winner = getTurn() == "white" ? "white" : "black";
                            ch.boardRefresh();
                            ch.sendMessage("Stablemate! \xF0\x9F\x98\x83");
                            break;
                        }
                        ch.boardRefresh();
                    }

                }
                else
                {
                    ch.sendMessage(getTurn() + ", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
                }   
            }
            else if (input == "s")
            {
                saveGame();
                exit(0);
            }
            else if (input == "q")
            {
                ch.sendMessage("Goodbye! \xF0\x9F\x98\x83");
                exit(0);
            }
            else
            {
                ch.sendMessage("Command nod recognized! \xF0\x9F\x98\x95");
                ch.sendMessage(getTurn() + ", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
            }
        }
        else
        {
            compMove();
        }
    }  
}
// Load saved game
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
        int x1 = stoi(i.substr(0,1));
        int y1 = stoi(i.substr(1,1));
        int x2 = stoi(i.substr(2,1));
        int y2 = stoi(i.substr(3,1));
        changePosition(x1,y1,x2,y2);
        changeTurn();
    }
    ch.sendMessage("Game is loaded! \xF0\x9F\x98\x83");
}
// Save unfinished game
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
    ch.sendMessage("Game is saved! \xF0\x9F\x98\x83");
}
// Start new game
void Game::startGame()
{
    board[0][0] = new Rook("white"), board[0][7] = new Rook("white");
    board[0][1] = new Knight("white"), board[0][6] = new Knight("white");  
    board[0][2] = new Bishop("white"), board[0][5] = new Bishop("white");
    board[0][3] = new Queen("white"), board[0][4] = new King("white");  
    board[7][0] = new Rook("black"), board[7][7] = new Rook("black");
    board[7][1] = new Knight("black"), board[7][6] = new Knight("black");   
    board[7][2] = new Bishop("black"), board[7][5] = new Bishop("black");
    board[7][3] = new Queen("black"), board[7][4] = new King("black");
    for(int i = 0; i<8; i++) {board[1][i] = new Pawn("white");}
    for(int i = 0; i<8; i++) {board[6][i] = new Pawn("black");}
    turn = 0;
    whiteKing[0] = 4, whiteKing[1] = 0;
    blackKing[0] = 4, blackKing[1] = 7;
}
// Return piece object located at square address
Piece* Game::getPiece(int x, int y)
{
    return board[y][x];
}
// Get current turn
string Game::getTurn()
{
    return turn == 0 ? "white" : "black";
}
// Change turn
void Game::changeTurn()
{
    turn = !turn;
}
// Save last king's location
void Game::moveKing(int x, int y)
{
    if (getTurn() == "white")
        whiteKing[0] = x, whiteKing[1] = y;
    else
        blackKing[0] = x, blackKing[1] = y;
}
// Verify if move is possible
bool Game::checkBoard(int x1, int y1, int x2, int y2)
{
    if (getPiece(x1,y1) == 0)
    {
        ch.sendMessage("There are no pieceses here! \xF0\x9F\x98\x95");
        return 0;
    }
    else if (getPiece(x1,y1)->getColor() != getTurn())
    {
        ch.sendMessage("It's "+ getTurn() +"'s turn to move now! \xF0\x9F\x98\x95");
        return 0;
    }
    else if (getPiece(x2,y2) != 0 && getPiece(x2,y2)->getColor() == getTurn())
    {
        ch.sendMessage("You can't capture own piece! \xF0\x9F\x98\x95");
        return 0;
    }
    else return 1;
}
// Change piece's position on the board
void Game::changePosition(int x1, int y1, int x2, int y2)
{
    if (getPiece(x1,y1)->getType() == "pawn" && getPiece(x2,y1) != 0 && getPiece(x2,y1)->getEnPassant() == 1)
    {
        board[y2][x2] = board[y1][x1];
        board[y1][x1] = 0;
        delete board[y1][x2];
        board[y1][x2] = 0;
    }
    else if (getPiece(x1,y1)->getType() == "king" && y1 == 0 && x1 == 4 && x2 == 2)
    {
        board[y2][x2] = board[y1][x1];
        board[y1][x1] = 0;
        board[0][3] = board[0][0];
        board[0][0] = 0;
    }
    else if (getPiece(x1,y1)->getType() == "king" && y1 == 0 && x1 == 4 && x2 == 6)
    {
        board[y2][x2] = board[y1][x1];
        board[y1][x1] = 0;
        board[0][5] = board[0][7];
        board[0][7] = 0;
    }
    else if (getPiece(x1,y1)->getType() == "king" && y1 == 7 && x1 == 4 && x2 == 2)
    {
        board[y2][x2] = board[y1][x1];
        board[y1][x1] = 0;
        board[7][3] = board[7][0];
        board[7][0] = 0;
    }
    else if (getPiece(x1,y1)->getType() == "king" && y1 == 7 && x1 == 4 && x2 == 6)
    {
        board[y2][x2] = board[y1][x1];
        board[y1][x1] = 0;
        board[7][5] = board[7][7];
        board[7][7] = 0;
    }
    else
    {
        if (getPiece(x2,y2) != 0)
            delete board[y2][x2];
        board[y2][x2] = board[y1][x1];
        board[y1][x1] = 0;
    }
}
// Save last move
void Game::saveMove(int x1, int y1, int x2, int y2)
{
    string move = to_string(x1) + to_string(y1) + to_string(x2) + to_string(y2);
    history.push_back(move);
}
// Clean board (used for simulating)
void Game::cleanBoard()
{
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if (getPiece(x,y) != 0)
            {
                delete board[y][x]; 
            }
        }
    }
}
// Simulate move and test if king isn't under attack
bool Game::simulateMove(int x1, int y1, int x2, int y2)
{
    array <array <Piece*,8>,8> sboard = board;
    bool isKing = getPiece(x1,y1)->getType() == "king";
    for (int y = 0; y < 8; y++)
    {
        for (int x = 0; x < 8; x++)
        {
            if (getPiece(x,y) != 0)
            {
                string color = getPiece(x,y)->getColor();
                if (getPiece(x,y)->getType() == "pawn")
                {
                    sboard[y][x] = new Pawn(color);
                    if (getPiece(x,y)->getEnPassant()) sboard[y][x]->setEnPassant();
                    if (getPiece(x,y)->getIsMoved()) sboard[y][x]->setMoved();
                }
                if (getPiece(x,y)->getType() == "bishop")
                    sboard[y][x] = new Bishop(color);
                if (getPiece(x,y)->getType() == "knight")
                    sboard[y][x] = new Knight(color);
                if (getPiece(x,y)->getType() == "rook")
                {
                    sboard[y][x] = new Rook(color);
                    if (getPiece(x,y)->getIsMoved()) sboard[y][x]->setMoved();
                }                 
                if (getPiece(x,y)->getType() == "queen")
                    sboard[y][x] = new Queen(color);
                if (getPiece(x,y)->getType() == "king")
                {
                    sboard[y][x] = new King(color);
                    if (getPiece(x,y)->getIsMoved()) sboard[y][x]->setMoved();
                }                
            }
        }
    }
    changePosition(x1,y1,x2,y2);
    if (isKing) moveKing(x2,y2);
    if (checkUnderAttack(getTurn()))
    {
        cleanBoard();
        board = sboard;
        if (isKing) moveKing(x1,y1);
        return 1;
    }
    else
    {
        cleanBoard();
        board = sboard;
        if (isKing) moveKing(x1,y1);
        return 0;
    }
}
// Check if king is under attack
bool Game::checkUnderAttack(string turn)
{
    int x2;
    int y2;
    if (getTurn() == "white")
    {
        x2 = whiteKing[0];
        y2 = whiteKing[1];
    }
    else
    {
        x2 = blackKing[0];
        y2 = blackKing[1];
    }
    for (int y1 = 0; y1 < 8; y1++)
    {
        for (int x1 = 0; x1 < 8; x1++)
        {
            if (getPiece(x1,y1) != 0 && getPiece(x1,y1)->getColor() != getTurn() && getPiece(x1,y1)->checkMove(x1,y1,x2,y2))
            {
                return 1;
            }
        }
    }
    return 0;
}
// Check if king is checkmated
bool Game::checkMate(string turn)
{
    for (int y1 = 0; y1 < 8; y1++)
    {
        for (int x1 = 0; x1 < 8; x1++)
        {
            if (getPiece(x1,y1) != 0 && getPiece(x1,y1)->getColor() == getTurn())
            {
                for (int y2 = 0; y2 < 8; y2++)
                {
                    for (int x2 = 0; x2 < 8; x2++)
                    {
                        if (!(getPiece(x2,y2) != 0 && getPiece(x2,y2)->getColor() == getTurn()) && getPiece(x1,y1)->checkMove(x1,y1,x2,y2) && !simulateMove(x1,y1,x2,y2))
                        {
                            return 0;
                        }
                    }
                }

            }
        }
    }
    return 1;
}
// Make next move for computer
void Game::compMove()
{
    map<int,string> dict = {{0,"a"},{1,"b"},{2,"c"},{3,"d"},{4,"e"},{5,"f"},{6,"g"},{7,"h"}};
    vector<array<int,4>> moves;
    int x1; int y1; int x2; int y2;
    string move;
    for (int y3 = 0; y3 < 8; y3++)
    {
        for (int x3 = 0; x3 < 8; x3++)
        {
            if (getPiece(x3,y3) != 0 && getPiece(x3,y3)->getColor() == getTurn())
            {
                for (int y4 = 0; y4 < 8; y4++)
                {
                    for (int x4 = 0; x4 < 8; x4++)
                    {
                        if ((getPiece(x4,y4) == 0 && getPiece(x3,y3)->checkMove(x3,y3,x4,y4) && !simulateMove(x3,y3,x4,y4)) ||
                            (getPiece(x4,y4) != 0 && getPiece(x4,y4)->getColor() != getTurn() && getPiece(x3,y3)->checkMove(x3,y3,x4,y4) && !simulateMove(x3,y3,x4,y4)))
                        {
                            array<int,4> temp = {x3,y3,x4,y4};
                            moves.push_back(temp);
                        }
                    }
                }
            }
        }
    }
    
    ch.sendMessage("I have "+ to_string(moves.size()) + " moves in this position");
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distr(1,moves.size());
    int i = distr(gen)-1;
    ch.sendMessage("I have chosen move number #" + to_string(i));
    x1 = moves[i][0];
    y1 = moves[i][1];
    x2 = moves[i][2];
    y2 = moves[i][3];
    move = dict[x1] + to_string(y1+1) + "-" + dict[x2] + to_string(y2+1);
    getPiece(x1,y1)->movePiece(x1,y1,x2,y2,move);
    ch.boardRefresh();
    ch.sendMessage(getTurn() + ", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?");
}