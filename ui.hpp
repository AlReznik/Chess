#pragma once
#include "base.hpp"
#include "piece.hpp"

/*! \file ui.hpp
* @brief class UI header file
*/

/**
 * @brief Class that implements user interface
 */

class UI
{
public:
/**
 * @brief Construct a new UI object
 */
    UI();
/**
 * @brief Refresh chessboard view on the screen after move
 */
    void refreshBoard(array <array <Piece*,8>,8>);
/**
 * @brief Show message to player
 */
    void sendMessage(string);
/**
 * @brief Get command from player
 */
    string getInput();
/**
 * @brief Check if player's command is correct
 */
    bool checkInput(string);
/**
 * @brief Parse player's command
 */
    int* parseCommand(string);
private:
/**
 * @brief Draw upper part of the chessboard
 */
    void roof();
/**
 * @brief Draw middle part of the chessboard
 */
    void ceiling();
/**
 * @brief Draw lower part of the chessboard
 */
    void floor();

};