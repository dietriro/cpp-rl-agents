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

using namespace std;

class Manager
{
public:
    Manager();

    // Implemented methods
    void createAgents(int number_agents);

private:
    vector<thread> agents_workers_;
};

#endif