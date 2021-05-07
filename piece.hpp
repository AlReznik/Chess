#pragma once
#include "base.hpp"

/*! \file piece.hpp
* @brief class Piece header file
*/

/**
 * @brief Abstract class that includes all types of pieces
 */

class Piece
{
public:
/**
 * @brief Constructor used for pawns
 */
    Piece(string, string, bool, bool);
/**
 * @brief Constructor used for all pieces but pawns
 */
    Piece(string, string, bool);
/**
 * @brief Get type the piece
 */
    string getType();
/**
 * @brief Get color of the piece
 */
    string getColor();
/**
 * @brief Check if the piece has been moved
 */
    bool getIsMoved();
/**
 * @brief Set the piece has been moved
 */
    void setMoved();
/**
 * @brief Check if the pawn can be captured en passant
 */
    bool getEnPassant();
/**
 * @brief Set pawn that can be captured en passant
 */
    void setEnPassant();
/**
 * @brief Get symbol of the piece
 */
    virtual string getSymbol() = 0;
/**
 * @brief Validate move of the piece
 */
    virtual bool checkMove(int, int, int, int, array <array <Piece*,8>,8>, bool) = 0; 
protected:
    string type; //!< Type of the piece
    string color; //!< Color of the piece
    bool isMoved; //!< If the piece has been moved
    bool isEnPassant; //!< If the piece is en passant
};