#ifndef POSITION
#define POSITION

#include <string>
#include <iostream>
#include <mutex>
#include <algorithm>
#include <memory>
#include <vector>
#include <fstream>
#include <sstream>
#include <ostream>

using namespace std;

class Position
{
public:
    Position(/* args */);
    Position(int x, int y);
    ~Position();

    Position& operator=(const Position &other);

    Position operator+(const Position &other) const;
    Position operator+(const int value) const;
    Position& operator+=(const Position &other);
    Position operator-(const Position &other) const;
    Position operator-(const int value) const;
    Position& operator-=(const Position &other);

    bool operator==(const Position &other);
    bool operator<(const Position &other) const;
    bool operator>(const Position &other) const;
    bool operator<=(const Position &other) const;
    bool operator>=(const Position &other) const;
    bool operator!=(const Position &other) const;

    int operator[](const int &index) const;
    friend ostream& operator<<(ostream &out, const Position &pos);

private:
    int x_, y_;
};

const Position ZERO_POS(0,0);

#endif