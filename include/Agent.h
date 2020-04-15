#ifndef AGENT
#define AGENT

#include <memory>
#include <vector>
#include <iostream>
#include <thread>

#include "Environment.h"

using namespace std;

class Agent
{
public:
    Agent(shared_ptr<Environment> env, Position pos);
    ~Agent();

    void run();
    void takeAction();
private:
    shared_ptr<Environment> env_;
    Position pos_;
    thread runner_;
};

#endif