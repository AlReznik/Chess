#include "base.hpp"
#include "game.hpp"
#include "king.hpp"
#include "queen.hpp"
#include "pawn.hpp"
#include "rook.hpp"
#include "knight.hpp"
#include "bishop.hpp"

Piece* board[8][8];
string history;
void startGame()
{
    board[0][0] = new Rook("white","a8"), board[0][7] = new Rook("white","a8");
    board[0][1] = new Knight("white","a8"), board[0][6] = new Knight("white","a8");  
    board[0][2] = new Bishop("white","a8"), board[0][5] = new Bishop("white","a8");
    board[0][3] = new Queen("white","a8"), board[0][4] = new King("white","a8");  
    board[7][0] = new Rook("black","a8"), board[7][7] = new Rook("black","a8");
    board[7][1] = new Knight("black","a8"), board[7][6] = new Knight("black","a8");   
    board[7][2] = new Bishop("black","a8"), board[7][5] = new Bishop("black","a8");
    board[7][3] = new Queen("black","a8"), board[7][4] = new King("black","a8");
    for(int i = 0; i<8; i++) {board[1][i] = new Pawn("white","a8");}
    for(int i = 0; i<8; i++) {board[6][i] = new Pawn("black","a8");}   
}
int* parseCommand(string str)
{
    map<string,int> dict = {{"a",0},{"b",1},{"c",2},{"d",3},{"e",4},{"f",5},{"g",6},{"h",7}};
    int* ar = new int[4];
    ar[0] = dict[str.substr(0,1)], ar[1] = stoi(str.substr(1,1))-1;
    ar[2] = dict[str.substr(3,1)], ar[3] = stoi(str.substr(4,1))-1;
    return ar;
}
Piece* getPiece(int x, int y)
{
    return board[y][x];
}
void changePosition(int x1, int y1, int x2, int y2)
{
    board[y2][x2] = board[y1][x1];
    board[y1][x1] = 0;
}
void loadGame()
{
    cout << "Load" << endl;
}
void saveGame()
{
    cout << "Save" << endl;
}
void roof()
{
    cout << "  \xE2\x95\xB7";
    for (int i = 0; i < 8; i++)
    {
        cout << "\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94\xE2\x95\xB7";    
    }
    cout <<"\n";
}
void ceiling()
{
    cout << "  |";
    for (int i = 0; i < 8; i++)
    {
        cout << "\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94|";    
    }
    cout <<"\n";
}
void floor()
{
    cout << "  \xE2\x95\xB5";
    for (int i = 0; i < 8; i++)
    {
        cout << "\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94\xE2\x95\xB5";    
    }
    cout <<"\n";
}
void boardRefresh()
{
    SetConsoleOutputCP(CP_UTF8);
    roof();
    for(int i = 0; i<8;i++)
    {
        cout << 8-i;
        cout << " |";
        for (int j = 0; j<8; j++)
        {
            if (board[7-i][j])
            {
                cout << " "+board[7-i][j]->getSymbol()+"  |";
            }
            else
            {
                cout << "    |";
            }
        }
        cout << "\n";
        i == 7 ? floor() : ceiling();
    }
    cout <<"    A    B    C    D    E    F    G    H   \n";
    
    cout << "Your move" << endl;
}
