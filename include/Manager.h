#ifndef MANAGER
#define MANAGER

#include <string>
#include <iostream>
#include <mutex>
#include <algorithm>
#include <memory>
#include <vector>
#include <thread>

#include "Agent.h"
#include "Environment.h"

using namespace std;

class Manager
{
public:
    Manager();

    // Implemented methods
    void createAgents(int number_agents, int x, int y);
    void runLearning(int number_runs, bool visualization);

private:
    shared_ptr<Environment> env_;

    vector<shared_ptr<Agent>> agents_;
    shared_ptr<Agent> target_;
    vector<thread> agent_workers_;
    thread target_worker_;
    thread visualizer_;

    shared_ptr<mutex> io_mutex_;
};

#endif