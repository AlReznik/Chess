#include "base.hpp"
#include "game.hpp"
#include "king.hpp"
#include "queen.hpp"
#include "pawn.hpp"
#include "rook.hpp"
#include "knight.hpp"
#include "bishop.hpp"

array <array <Piece*,8>,8> board;
deque <string> history;
bool turn;
int whiteKing[2];
int blackKing[2];

// Check if player's input is correct
bool checkInput(string input)
{
    string letters[8] = {"a","b","c","d","e","f","g","h"};
    string digits[8] = {"1","2","3","4","5","6","7","8"};
    if (input.size() == 5 && find(begin(letters),end(letters),input.substr(0,1))!=end(letters) &&
    find(begin(digits),end(digits),input.substr(1,1))!=end(digits) && find(begin(letters),end(letters),input.substr(3,1))!=end(letters) &&
    find(begin(digits),end(digits),input.substr(4,1))!=end(digits) && input.substr(2,1)=="-")
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
// Load saved game
void loadGame()
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
    sendMessage("Game is loaded! \xF0\x9F\x98\x83");
}
// Save unfinished game
void saveGame()
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
    sendMessage("Game is saved! \xF0\x9F\x98\x83");
}
// Start new game
void startGame()
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
// Parse input string and return an array of square addresses for move
int* parseCommand(string str)
{
    map<string,int> dict = {{"a",0},{"b",1},{"c",2},{"d",3},{"e",4},{"f",5},{"g",6},{"h",7}};
    int* ar = new int[4];
    ar[0] = dict[str.substr(0,1)], ar[1] = stoi(str.substr(1,1))-1;
    ar[2] = dict[str.substr(3,1)], ar[3] = stoi(str.substr(4,1))-1;
    return ar;
}
// Return piece object located at square address
Piece* getPiece(int x, int y)
{
    return board[y][x];
}
// Get current turn
string getTurn()
{
    return turn == 0 ? "white" : "black";
}
// Change turn
void changeTurn()
{
    turn = !turn;
}
// Save last king's location
void moveKing(int x, int y)
{
    if (getTurn() == "white")
        whiteKing[0] = x, whiteKing[1] = y;
    else
        blackKing[0] = x, blackKing[1] = y;
}
// Verify if move is possible
bool checkBoard(int x1, int y1, int x2, int y2)
{
    if (getPiece(x1,y1) == 0)
    {
        sendMessage("There are no pieceses here! \xF0\x9F\x98\x95");
        return 0;
    }
    else if (getPiece(x1,y1)->getColor() != getTurn())
    {
        sendMessage("It's "+ getTurn() +"'s turn to move now! \xF0\x9F\x98\x95");
        return 0;
    }
    else if (getPiece(x2,y2) != 0 && getPiece(x2,y2)->getColor() == getTurn())
    {
        sendMessage("You can't capture own piece! \xF0\x9F\x98\x95");
        return 0;
    }
    else return 1;
}
// Change piece's position on the board
void changePosition(int x1, int y1, int x2, int y2)
{
    if (getPiece(x1,y1)->getType() == "pawn" && getPiece(x2,y1) != 0 && getPiece(x2,y1)->getEnPassant() == 1)
    {
        board[y2][x2] = board[y1][x1];
        board[y1][x1] = 0;
        delete board[y1][x2];
        board[y1][x2] = 0;
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
void saveMove(int x1, int y1, int x2, int y2)
{
    string move = to_string(x1) + to_string(y1) + to_string(x2) + to_string(y2);
    history.push_back(move);
}
// Clean board (used for simulating)
void cleanBoard()
{
    for (int y = 0; y < 8; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            if (getPiece(x,y) != 0)
            {
                delete board[y][x]; 
            }
        }
    }
}
// Simulate move and test if king isn't under attack
bool simulateMove(int x1, int y1, int x2, int y2)
{
    array <array <Piece*,8>,8> sboard = board;
    for (int y = 0; y < 8; ++y)
    {
        for (int x = 0; x < 8; ++x)
        {
            if (getPiece(x,y) != 0)
            {
                string color = getPiece(x,y)->getColor();
                if (getPiece(x,y)->getType() == "pawn")
                    sboard[y][x] = new Pawn(color);
                if (getPiece(x,y)->getType() == "bishop")
                    sboard[y][x] = new Bishop(color);
                if (getPiece(x,y)->getType() == "knight")
                    sboard[y][x] = new Knight(color);
                if (getPiece(x,y)->getType() == "rook")
                    sboard[y][x] = new Rook(color);
                if (getPiece(x,y)->getType() == "queen")
                    sboard[y][x] = new Queen(color);
                if (getPiece(x,y)->getType() == "king")
                    sboard[y][x] = new King(color);
            }
        }
    }
    changePosition(x1,y1,x2,y2);
    if (checkUnderAttack(getTurn()))
    {
        cleanBoard();
        board = sboard;
        return 1;
    }
    else
    {
        cleanBoard();
        board = sboard;
        return 0;
    }
}
// Check if king is under attack
bool checkUnderAttack(string turn)
{
    int x2;
    int y2;
    if (turn == "white")
    {
        x2 = whiteKing[0];
        y2 = whiteKing[1];
    }
    else
    {
        x2 = blackKing[0];
        y2 = blackKing[1];
    }
    for (int y1 = 0; y1 < 8; ++y1)
    {
        for (int x1 = 0; x1 < 8; ++x1)
        {
            if (getPiece(x1,y1) != 0 && getPiece(x1,y1)->getColor() != turn && getPiece(x1,y1)->checkMove(x1,y1,x2,y2))
            {
                return 1;
            }
        }
    }
    return 0;
}
// Check if king is checkmated
bool checkMate(string turn)
{
    int x2;
    int y2;
    if (turn == "white")
    {
        x2 = whiteKing[0];
        y2 = whiteKing[1];
    }
    else
    {
        x2 = blackKing[0];
        y2 = blackKing[1];
    }
    for (int y1 = 0; y1 < 8; ++y1)
    {
        for (int x1 = 0; x1 < 8; ++x1)
        {
            if (getPiece(x2,y2)->checkMove(x2,y2,x1,y1) && !simulateMove(x2,y2,x1,y1))
            {
                cout << x2<< y2<<x1<<y1<<endl;
                return 0;
            }
        }
    }
    return 1;
}
// Check if king is stalemated
bool checkStalemate(string turn)
{
    return 0;
}