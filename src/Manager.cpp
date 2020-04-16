#include "Manager.h"

Manager::Manager()
{
    io_mutex_ = make_shared<mutex>();
}


void Manager::createAgents(int number_agents, int x, int y)
{
    env_ = make_shared<Environment>(io_mutex_, x, y);
    target_ = make_shared<Agent>(env_, env_->generatePosition(), -1, io_mutex_, true);
    env_->setTarget(target_);

    for (int i=0; i<number_agents; i++)
    {
        agents_.emplace_back(make_shared<Agent>(env_, env_->generatePosition(), i, io_mutex_));
        weak_ptr<Agent> agent = agents_.back(); 
        env_->addAgent(move(agent));
    }
    
    cout << "[Manager]: Created " << number_agents << " new agents and 1 target" << endl;
}

void Manager::runLearning(int number_runs, bool visualization)
{
    for (int run=0; run<number_runs; run++)
    {
        cout << endl << "[Manager]: Starting learning run # " << run+1 << endl;

        // Start target and agents
        target_worker_ = move(thread(&Agent::run, target_));

        for (int i=0; i<agents_.size(); i++)
        {
            if (agent_workers_.size() < agents_.size())
                agent_workers_.emplace_back(&Agent::run, agents_[i]);
            else
                agent_workers_[i] = move(thread(&Agent::run, agents_[i]));
        }
        if (visualization)
            visualizer_ = move(thread(&Environment::visualize, env_, 1));

        cout << "[Manager]: Started all agents, waiting for them to finish now..." << endl;

        // Wait for target and agents to finish
        for (int i=0; i<agent_workers_.size(); i++)
        {
            agent_workers_[i].join();
        }
        target_worker_.join();
        if (visualization)
            visualizer_.join();

        cout << "[Manager]: Finished learning run # " << run+1 << endl;
    }

}
