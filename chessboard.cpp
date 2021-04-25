#include "base.hpp"
#include "chessboard.hpp"
#include "game.hpp"

extern Game g;
Chessboard::Chessboard()
{
    SetConsoleOutputCP(CP_UTF8);
    sendMessage("Welcome to Console Chess App! \xF0\x9F\x98\x83");
    sendMessage("Do you want to load saved game(L), start new game(N), play with computer(C) or quit(Q)?");
}
// Draw upper part of the board
void Chessboard::roof()
{
    cout << "  \xE2\x95\xB7";
    for (int i = 0; i < 8; i++)
    {
        cout << "\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94\xE2\x95\xB7";    
    }
    cout <<"\n";
}
// Draw middle part of the board
void Chessboard::ceiling()
{
    cout << "  |";
    for (int i = 0; i < 8; i++)
    {
        cout << "\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94|";    
    }
    cout <<"\n";
}
// Draw lower part of the board
void Chessboard::floor()
{
    cout << "  \xE2\x95\xB5";
    for (int i = 0; i < 8; i++)
    {
        cout << "\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94\xE2\x95\xB5";    
    }
    cout <<"\n";
}
// Refresh board after moving pieces
void Chessboard::boardRefresh()
{
    roof();
    for(int i = 0; i<8;i++)
    {
        cout << 8-i;
        cout << " |";
        for (int j = 0; j<8; j++)
        {
            if (g.getPiece(j,7-i))
            {
                cout << " " + g.getPiece(j,7-i)->getSymbol()+"  |";
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
}
// Send message to player
void Chessboard::sendMessage(string str)
{
    cout << str << endl;
}
// Get player's input
string Chessboard::getInput()
{
    string input;
    cin >> input;
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    return input;
}
// Check if player's input is correct
bool Chessboard::checkInput(string input)
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
// Parse input string and return an array of square addresses for move
int* Chessboard::parseCommand(string str)
{
    map<string,int> dict = {{"a",0},{"b",1},{"c",2},{"d",3},{"e",4},{"f",5},{"g",6},{"h",7}};
    int* ar = new int[4];
    ar[0] = dict[str.substr(0,1)], ar[1] = stoi(str.substr(1,1))-1;
    ar[2] = dict[str.substr(3,1)], ar[3] = stoi(str.substr(4,1))-1;
    return ar;
}