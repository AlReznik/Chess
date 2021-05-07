#pragma once
#include "base.hpp"
#include "piece.hpp"
#include "king.hpp"
#include "queen.hpp"
#include "pawn.hpp"
#include "rook.hpp"
#include "knight.hpp"
#include "bishop.hpp"
#include "ui.hpp"
#include "board.hpp"

/*! \file game.hpp
* @brief class Game header file
*/

/**
 * @brief Class that implements gaming process
 */

class Game
{
public:
/**
 * @brief Construct a new Game object
 */
    Game();
private:
/**
 * @brief Game introduction
 */
    void intro();
/**
 * @brief Play two players game
 */
    void playGame();
/**
 * @brief Load saved game
 */
    void loadGame();
/**
 * @brief Save unfinished game
 */
    void saveGame();
/**
 * @brief Start initial stage
 */
    void startGame();
    vector <string> history; //!< history of movents in the game
    Board b; //!< board object
    UI ui; //!< user interface object
};