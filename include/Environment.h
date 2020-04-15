#ifndef ENVIRONMENT
#define ENVIRONMENT

#include <string>
#include <iostream>
#include <mutex>
#include <algorithm>
#include <memory>
#include <vector>
#include <fstream>
#include <sstream>

#include "Agent.h"

using namespace std;

enum State
{
    free = 0,
    occupied = 1
};



class Position
{
public:
    Position(/* args */);
    Position(int x, int y);
    ~Position();

    Position operator+(const Position &other) const;
    Position& operator+=(const Position &other);
    Position operator-(const Position &other) const;
    Position& operator-=(const Position &other);
    bool operator<(const Position &other) const;
    bool operator>(const Position &other) const;
    bool operator<=(const Position &other) const;
    bool operator>=(const Position &other) const;

private:
    int x_, y_;
};

const Position ZERO_POS(0,0);

class Environment
{
public:
    Environment();

    // Implemented methods
    void loadMapFromFile(string file_name);
    void visualizePath(const vector<vector<int>> &path);

    void createAgents(int number_agents);

    bool posInBoundaries(const Position &pos);

private:
    Position generatePosition();

    Position size_;
    unique_ptr<vector<vector<short>>> map_;
    vector<unique_ptr<Agent>> agents_;
};

#endif