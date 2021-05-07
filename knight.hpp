#pragma once
#include "base.hpp"
#include "piece.hpp"

/*! \file knight.hpp
* @brief class Knight header file
*/

/**
 * @brief Class describing knights
 */

class Knight : public Piece
{
public:
    Knight(string);
    string getSymbol() override;
    bool checkMove(int, int, int, int, array <array <Piece*,8>,8>, bool) override;
};