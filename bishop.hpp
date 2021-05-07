#pragma once
#include "base.hpp"
#include "piece.hpp"

/*! \file bishop.hpp
* @brief class Bishop header file
*/

/**
 * @brief Class describing bishops
 */

class Bishop : public Piece
{
public:
/**
 * @brief Construct a new Bishop object
 */
    Bishop(string);
/**
 * @brief Get symbol of the bishop
 */
    string getSymbol() override;
/**
 * @brief Validate bishop's move
 */
    bool checkMove(int, int, int, int, array <array <Piece*,8>,8>, bool) override;
};