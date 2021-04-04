#include "base.hpp"
#include "piece.hpp"
#include "game.hpp"

int main()
{
    StartGame();
    BoardRefresh();
    cout << "Make you move\n";
    string input;
/*     cin >> input;
    if(input == "e2-e4")
    {
        cout << getPiece(0,0)->getSymbol() << endl;
        int* str[4] = parseString(input);
        getPiece(0,0)->movePiece(str[0],str[1],str[2],str[3]);
    } */
    BoardRefresh();
    cin >> input;

    return 0;
}