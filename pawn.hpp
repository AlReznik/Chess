#pragma once
#include "base.hpp"
#include "piece.hpp"

/*! \file pawn.hpp
* @brief class Pawn header file
*/

/**
 * @brief Class describing pawns
 */

class Pawn : public Piece
{
public:
/**
 * @brief Construct a new Pawn object
 */
    Pawn(string);
/**
 * @brief Get symbol of the pawn
 */ 
    string getSymbol() override;
/**
 * @brief Validate pawn's move
 */
    bool checkMove(int, int, int, int, array <array <Piece*,8>,8>, bool) override;
};