#include "piece.hpp"

// Constructor used for pawns
Piece::Piece(string type, string color, bool isMoved, bool isEnPassant)
{
    this->type = type;
    this->color = color;
    this->isMoved = isMoved;
    this->isEnPassant = isEnPassant;
}
// Main constructor
Piece::Piece(string type, string color, bool isMoved)
{
    this->type = type;
    this->color = color;
    this->isMoved = isMoved;
}
// Get type of the piece
string Piece::getType()
{
    return this->type;
}
// Get color of the piece
string Piece::getColor()
{
    return this->color;
}
// Check if pawn can be captured en passant
bool Piece::getEnPassant()
{
    return this->isEnPassant;
}