#pragma once
#include "base.hpp"
#include "piece.hpp"
#include "ui.hpp"

/*! \file board.hpp
* @brief class Board header file
*/

/**
 * @brief Class that implements chessboard
 */

class Board
{
    friend class Game;
public:
/**
 * @brief Construct a new Board object
 */
    Board();
/**
 * @brief Get piece object located at square address
 */
    Piece* getPiece(int, int);
/**
 * @brief Create a piece object at specific sqaure address
 */
    void setPiece(int, int, string, int);
/**
 * @brief Change location of piece object
 */
    void changePosition(int, int, int, int);
/**
 * @brief Get current position on the board
 */
    array <array <Piece*,8>,8> getBoard();
/**
 * @brief Attempt to move
 */
    bool nextMove(int, int, int, int, string, UI);
/**
 * @brief Get turn
 */
    string getTurn();
/**
 * @brief Change turn
 */
    void changeTurn();
/**
 * @brief Move the piece
 */
    void movePiece(int, int, int, int, string, UI);
/**
 * @brief Game introduction
 */
    void moveKing(int, int);
/**
 * @brief Save new king's position
 */
    bool checkBoard(int, int, int, int, UI);
/**
 * @brief Simulate move and test if king is under attack
 */
    bool simulateMove(int, int, int, int);
/**
 * @brief Check if king is being checked
 */
    bool checkUnderAttack(string);
/**
 * @brief Check if king is checkmated
 */
    bool checkMate(string);
/**
 * @brief Make computer move
 */
    void compMove(UI);
/**
 * @brief Promote pawn
 */
    void promotePawn(int, int, UI);
private:
    array <array <Piece*,8>,8> board; //!< board of pieces
    bool compgame; //!< if game with computer mode is chosen
    bool turn; //!< current turn to move
    bool check; //!< if the king is being checked
    int whiteKing[2]; //!< white king's current position
    int blackKing[2]; //!< black king's current position
};