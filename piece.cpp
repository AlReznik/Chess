#include "piece.hpp"

/*! \file piece.cpp
* @brief class Piece definition file
*/

/**
 * Parent constructor designed for creating objects of class Pawn
 * 
 * @param type describes type of the piece
 * @param color describes color of the piece
 * @param isMoved keeps info if the piece has been moved
 * @param isEnPassant keeps info if the piece is en passant
 */
Piece::Piece(string type, string color, bool isMoved, bool isEnPassant)
{
    this->type = type;
    this->color = color;
    this->isMoved = isMoved;
    this->isEnPassant = isEnPassant;
}

/**
 * Parent constructor designed for creating objects of classes Bishop, King, Knight, Queen and Rook
 * 
 * @param type describes type of the piece
 * @param color describes color of the piece
 * @param isMoved keeps info if the piece has been moved
 */
Piece::Piece(string type, string color, bool isMoved)
{
    this->type = type;
    this->color = color;
    this->isMoved = isMoved;
}

/**
 * @return type of the piece 
 */
string Piece::getType()
{
    return this->type;
}

/**
 * @return color of the piece 
 */
string Piece::getColor()
{
    return this->color;
}

/**
 * @return true if pawn can be captured en passant 
 */
bool Piece::getEnPassant()
{
    return this->isEnPassant;
}

void Piece::setEnPassant()
{
    this->isEnPassant = true;
}

/**
 * @return true if the piece has been moved
 */
bool Piece::getIsMoved()
{
    return this->isMoved;
}

void Piece::setMoved()
{
    this->isMoved = true;
}