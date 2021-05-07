#pragma once
#include "base.hpp"
#include "piece.hpp"

/*! \file rook.hpp
* @brief class Rook header file
*/

/**
 * @brief Class describing rooks
 */

class Rook : public Piece
{
public:
/**
 * @brief Construct a new Rook object
 */
    Rook(string);
/**
 * @brief Get symbol of the rook
 */
    string getSymbol() override;
/**
 * @brief Validate rook's move
 */
    bool checkMove(int, int, int, int, array <array <Piece*,8>,8>, bool) override;
};