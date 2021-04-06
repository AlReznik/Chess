#include "base.hpp"
#include "piece.hpp"
#include "game.hpp"

int main()
{
    startGame();
    boardRefresh();
    string input;
    while (true)
    {
        cin >> input;
        int x1 = parseCommand(input)[0]; int y1 = parseCommand(input)[1];
        int x2 = parseCommand(input)[2]; int y2 = parseCommand(input)[3];
        cout << x1 << " " << y1 << " " << x2 << " " << y2 << endl;
        cout << getPiece(x1,y1)->getSymbol() << endl;
        getPiece(x1,y1)->movePiece(x1,y1,x2,y2);
        boardRefresh();
    }
        
    return 0;
}