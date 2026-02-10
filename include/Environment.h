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
#include "Position.h"

using namespace std;

// enum State
// {
//     free = 0,
//     occupied = 1
// };

namespace CellState
{
    const string free = "▢";
    const string agent = "🚓";
    const string target = "🚗";
};

class Agent;

class Environment
{
public:
    Environment(shared_ptr<mutex> io_mutex, int size_x, int size_y);

    // Implemented methods
    void loadMapFromFile(string file_name);
    void visualize(int rate, bool reset_cursor_pos=true);

    // void createAgents(int number_agents);
    void addAgent(weak_ptr<Agent> agent);

    bool posInBoundaries(const Position &pos);
    bool caughtTarget(const Position &pos);

    Position getTargetPosition();
    Position getSize();

    void setTarget(weak_ptr<Agent> target);

    Position generatePosition();
private:
    Position size_;
    unique_ptr<vector<vector<short>>> map_;
    vector<weak_ptr<Agent>> agents_;
    weak_ptr<Agent> target_;
    mutex mutex_;
    shared_ptr<mutex> io_mutex_;

    static bool init_;
};

#endif