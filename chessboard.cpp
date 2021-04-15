#include "base.hpp"
#include "chessboard.hpp"
#include "game.hpp"

// Draw upper part of the board
void roof()
{
    cout << "  \xE2\x95\xB7";
    for (int i = 0; i < 8; i++)
    {
        cout << "\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94\xE2\x95\xB7";    
    }
    cout <<"\n";
}
// Draw middle part of the board
void ceiling()
{
    cout << "  |";
    for (int i = 0; i < 8; i++)
    {
        cout << "\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94|";    
    }
    cout <<"\n";
}
// Draw lower part of the board
void floor()
{
    cout << "  \xE2\x95\xB5";
    for (int i = 0; i < 8; i++)
    {
        cout << "\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94\xE2\x95\xB5";    
    }
    cout <<"\n";
}
// Refresh board after moving pieces
void boardRefresh()
{
    roof();
    for(int i = 0; i<8;i++)
    {
        cout << 8-i;
        cout << " |";
        for (int j = 0; j<8; j++)
        {
            if (getPiece(j,7-i))
            {
                cout << " " + getPiece(j,7-i)->getSymbol()+"  |";
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
    
    cout << getTurn() <<", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?" << endl;
}
// Send message to player
void sendMessage(string str)
{
    cout << str << endl;
}
// Get player's input
string getInput()
{
    string input;
    cin >> input;
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    return input;
}
