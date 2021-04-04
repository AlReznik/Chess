#include "base.hpp"
#include "game.hpp"

void Game::StartGame()
{
    board[0][0] = "\xE2\x99\x9C", board[0][7] = "\xE2\x99\x9C", board[0][1] = "\xE2\x99\x9E", board[0][6] = "\xE2\x99\x9E";  
    board[0][2] = "\xE2\x99\x9D", board[0][5] = "\xE2\x99\x9D", board[0][3] = "\xE2\x99\x9B", board[0][4] = "\xE2\x99\x9A";  
    board[7][0] = "\xE2\x99\x96", board[7][7] = "\xE2\x99\x96", board[7][1] = "\xE2\x99\x98", board[7][6] = "\xE2\x99\x98";   
    board[7][2] = "\xE2\x99\x97", board[7][5] = "\xE2\x99\x97", board[7][3] = "\xE2\x99\x95", board[7][4] = "\xE2\x99\x94";
    
    for(int i = 0; i<8; i++) {board[1][i] = "\xE2\x99\x9F";}
    for(int i = 0; i<8; i++) {board[6][i] = "\xE2\x99\x99";}
    for(int i = 2; i<6; i++)
    {
        for(int j = 0; j<8; j++)
        {
            board[i][j] = " ";
        }
    }
}

void Game::LoadGame()
{
    cout << "Load" << endl;
}
void Game::SaveGame()
{
    cout << "Save" << endl;
}