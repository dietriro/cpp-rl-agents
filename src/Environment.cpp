#include "Environment.h"

///////////////// Class: Position

Position::Position()
{
}

Position::Position(int x, int y): x_{x}, y_{y}
{

}

Position::~Position()
{
}

Position Position::operator+(const Position &other) const
{
    return Position(x_+other.x_, y_+other.y_);
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

Position& Position::operator-=(const Position &other)
{
    x_ -= other.x_;
    y_ -= other.y_; 
    return *this;
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




///////////////// Class: Environment 

Environment::Environment() 
{
    
}

void Environment::loadMapFromFile(string file_name) 
{
    fstream fstr(file_name);
    string line;

    while (getline(fstr, line))
    {
        istringstream sline(line);
        short n;
        char c;
        vector<short> row;
        while (sline >> n >> c && c == ',') 
        {
            row.push_back(n);
        }
        map_->push_back(row);
    }
}

void Environment::visualizePath(const vector<vector<int>> &path) 
{
    
}

void Environment::createAgents(int number_agents) 
{
    for (int i=0; i<number_agents; i++)
    {
        Position new_pos = generatePosition();
        agents_.emplace_back(make_unique<Agent>(shared_ptr<Environment>(this), new_pos));
    }
}

bool Environment::posInBoundaries(const Position &pos)
{
    return pos >= ZERO_POS && pos < size_;
}
