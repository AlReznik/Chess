#include "piece.hpp"

Piece::Piece(string type, string color, string position, bool isMoved)
{
    this->type = type;
    this->color = color;
    this->position = position;
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

void Piece::setPosition(string position)
{
    this->position = position;
}