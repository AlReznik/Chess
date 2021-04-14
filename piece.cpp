#include "piece.hpp"

Piece::Piece(string type, string color, bool isMoved, bool isEnPassant)
{
    this->type = type;
    this->color = color;
    this->isMoved = isMoved;
    this->isEnPassant = isEnPassant;
}
Piece::Piece(string type, string color, bool isMoved)
{
    this->type = type;
    this->color = color;
    this->isMoved = isMoved;
}
string Piece::getType()
{
    return this->type;
}
string Piece::getPosition()
{
    return this->type;
}
string Piece::getColor()
{
    return this->color;
}
bool Piece::getEnPassant()
{
    return this->isEnPassant;
}
void Piece::setPosition(string position)
{
    this->position = position;
}