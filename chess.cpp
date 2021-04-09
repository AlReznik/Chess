#include "base.hpp"
#include "piece.hpp"
#include "game.hpp"
#include <algorithm>
#include <iterator>

bool checkInput(string input)
{
    string letters[8] = {"a","b","c","d","e","f","h"};
    string digits[8] = {"1","2","3","4","5","6","7","8"};
    if (find(begin(letters),end(letters),input.substr(0,1))!=end(letters) && find(begin(digits),end(digits),input.substr(1,1))!=end(digits) &&
    find(begin(letters),end(letters),input.substr(3,1))!=end(letters) && find(begin(digits),end(digits),input.substr(4,1))!=end(digits) &&
    input.substr(2,1)=="-")
    {
        return 1;
    }
    else
    {
        return 0;
    }
};
int main()
{
    cout << "Welcome to Console Chess App!\nDo you want to load saved game(L), start new game(N) or quit(q)?" <<endl;
    string start;
    while(true)
    {
        cin >> start;
        if (start == "l" || start == "L")
        {
            cout << "Loading game" << endl;
            break;
        }
        else if (start == "q" || start == "Q")
        {
            cout << "Goodbye!" << endl;
            return 0;
        }
        else if (start == "n" || start == "N")
        {
            startGame();
            boardRefresh();
            break;
        }
        else
        {
            cout << "Command nod recognized!" << endl;
            cout << "Do you want to load saved game(L) or start new game(N)?" <<endl;
        }
    }

    string input;
    while (true)
    {
        cin >> input;
        transform(input.begin(), input.end(), input.begin(), ::tolower);
        if (input.size() == 5 && checkInput(input) == 1)
        {
            int x1 = parseCommand(input)[0]; int y1 = parseCommand(input)[1];
            int x2 = parseCommand(input)[2]; int y2 = parseCommand(input)[3];
            if (checkBoard(x1,y1,x2,y2))
            {
                getPiece(x1,y1)->movePiece(x1,y1,x2,y2,input);
                boardRefresh();
            }
            else
            {
                cout << getTurn() <<", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?" << endl;
            }   
        }
        else if (input == "s" || input == "S")
        {
            cout << "Goodbye!!" << endl;
            break;
        }
        else if (input == "q" || input == "Q")
        {
            cout << "Goodbye!" << endl;
            return 0;
        }
        else
        {
            cout << "Command nod recognized!" << endl;
            cout << getTurn() <<", make your move typing command in #0-#0 format, save game(S) or quit without saving(Q)?" << endl;
        }

    }
        
    return 0;
}