#ifndef AGENT
#define AGENT

#include <memory>
#include <vector>
#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <functional>

#include "Environment.h"
#include "Position.h"

using namespace std;

class Position;
class Environment;

enum ACTION
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
};

const Position Actions[] = {{0,1}, {0,-1}, {-1,0}, {1,0}};
const int REWARD_TIME = -2;
const int REWARD_CATCH = -2;
const int G = 0.75;

class Agent
{
    friend class Environment;
public:
    Agent(shared_ptr<Environment> env, Position pos, int id, shared_ptr<mutex> io_mutex, bool random=false);
    ~Agent();

    void run();
    int takeAction();

    Position getPos();

    static bool targetCaught();

private:
    void updateActionValues(vector<short> &action_values);
    void updateQ(int action_id);

    shared_ptr<Environment> env_;
    Position pos_;
    bool random_;
    unique_ptr<vector<vector<vector<short>>>> q_;
    Position last_dist_;
    int num_iterations_;
    int id_;
    mutex mutex_;
    shared_ptr<mutex> io_mutex_;
    
    static mutex class_mutex_;
    static bool init_;
    static bool caught_;
};

#endif