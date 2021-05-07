#pragma once
#include "base.hpp"
#include "piece.hpp"

/*! \file queen.hpp
* @brief class Queen header file
*/

/**
 * @brief Class describing queens
 */

class Queen : public Piece
{
public:
/**
 * @brief Construct a new Queen object
 */
    Queen(string);
/**
 * @brief Get symbol of the queen
 */
    string getSymbol() override;
/**
 * @brief Validate bishop's move
 */
    bool checkMove(int, int, int, int, array <array <Piece*,8>,8>, bool) override;
};