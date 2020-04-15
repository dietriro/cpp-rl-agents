#include "Agent.h"

Agent::Agent(shared_ptr<Environment> env, Position pos) : env_{env}, pos_{pos}
{
    runner_ = thread(&Agent::run, this);
}

Agent::~Agent()
{
    runner_.join();
}

void run()
{

}

void takeAction()
{

}