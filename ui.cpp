#include "base.hpp"
#include "ui.hpp"

/*! \file ui.cpp
* @brief class UI definition file
*/

/**
 * Construct an object of class UI
 * Set console to UTF output
 * Show introducing message and offer to choose game mode
 */
UI::UI()
{
    SetConsoleOutputCP(CP_UTF8);
    sendMessage("Welcome to Console Chess App! \xF0\x9F\x98\x83");
    sendMessage("Do you want to load saved game(L), start new game(N), play with computer(C) or quit(Q)?");
}

void UI::roof()
{
    cout << "  \xE2\x95\xB7";
    for (int i = 0; i < 8; i++)
    {
        cout << "\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94\xE2\x95\xB7";    
    }
    cout <<"\n";
}

void UI::ceiling()
{
    cout << "  |";
    for (int i = 0; i < 8; i++)
    {
        cout << "\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94|";    
    }
    cout <<"\n";
}

void UI::floor()
{
    cout << "  \xE2\x95\xB5";
    for (int i = 0; i < 8; i++)
    {
        cout << "\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94\xE2\x80\x94\xE2\x95\xB5";    
    }
    cout <<"\n";
}
/**
 * @param board pass current position on the board
 */
void UI::refreshBoard(array <array <Piece*,8>,8> board)
{
    roof();
    for(int i = 0; i<8; i++)
    {
        cout << 8-i;
        cout << " |";
        for (int j = 0; j<8; j++)
        {
            if (board[7-i][j])
            {
                cout << " " + board[7-i][j]->getSymbol()+"  |";
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

/**
 * @param str message for showing to player
 */
void UI::sendMessage(string str)
{
    cout << str << endl;
}

string UI::getInput()
{
    string input;
    cin >> input;
    transform(input.begin(), input.end(), input.begin(), ::tolower);
    return input;
}
/**
 * @param input player's input string
 * @return true if input string matchs the pattern #0-#0
 */
bool UI::checkInput(string input)
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

/**
 * @param str input string
 * @return array of square addresses for move
 */
int* UI::parseCommand(string str)
{
    map<string,int> dict = {{"a",0},{"b",1},{"c",2},{"d",3},{"e",4},{"f",5},{"g",6},{"h",7}};
    int* ar = new int[4];
    ar[0] = dict[str.substr(0,1)], ar[1] = stoi(str.substr(1,1))-1;
    ar[2] = dict[str.substr(3,1)], ar[3] = stoi(str.substr(4,1))-1;
    return ar;
}