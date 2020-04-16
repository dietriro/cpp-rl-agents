#include "Position.h"


Position::Position()
{
}

Position::Position(int x, int y): x_{x}, y_{y}
{

}

Position::~Position()
{
}

Position& Position::operator=(const Position &other)
{
    x_ = other.x_;
    y_ = other.y_;
    return *this;
}

Position Position::operator+(const Position &other) const
{
    return Position(x_+other.x_, y_+other.y_);
}

Position Position::operator+(const int value) const
{
    return Position(x_+value, y_+value);
}

Position& Position::operator+=(const Position &other)
{
    x_ += other.x_;
    y_ += other.y_; 
    return *this;
}

Position Position::operator-(const Position &other) const
{
    return Position(x_-other.x_, y_-other.y_);
}

Position Position::operator-(const int value) const
{
    return Position(x_-value, y_-value);
}

Position& Position::operator-=(const Position &other)
{
    x_ -= other.x_;
    y_ -= other.y_; 
    return *this;
}

bool Position::operator==(const Position &other)
{
    return x_ == other.x_ && y_ == other.y_;
}

bool Position::operator<(const Position &other) const
{
    return x_ < other.x_ && y_ < other.y_;
}

bool Position::operator>(const Position &other) const
{
    return x_ > other.x_ && y_ > other.y_;
}

bool Position::operator<=(const Position &other) const
{
    return x_ <= other.x_ && y_ <= other.y_;
}

bool Position::operator>=(const Position &other) const
{
    return x_ >= other.x_ && y_ >= other.y_;
}

bool Position::operator!=(const Position &other) const
{
    return x_ != other.x_ && y_ != other.y_;
}

int Position::operator[](const int &index) const
{
    if (index == 0)
        return x_;
    else if (index == 1)
        return y_;
    else
        throw out_of_range("Tried to access invalid member of Posision. Only 0 and 1 are allowed");
}

ostream& operator<<(ostream &out, const Position &pos)
{
    out << "(" + to_string(pos.x_) + ", " + to_string(pos.y_) + ")";
    return out;
}

