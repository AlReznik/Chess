#pragma once
#include "base.hpp"
#include "piece.hpp"

/*! \file king.hpp
* @brief class King header file
*/

/**
 * @brief Class describing kings
 */

class King : public Piece
{
public:
/**
 * @brief Construct a new King object
 */
    King(string);
/**
 * @brief Get symbol of the king
 */   
    string getSymbol() override;
/**
 * @brief Validate king's move
 */
    bool checkMove(int, int, int, int, array <array <Piece*,8>,8>, bool) override;
};