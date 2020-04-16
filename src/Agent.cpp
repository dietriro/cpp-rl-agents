#include "Agent.h"

template <typename T>
T randMaxElement(const vector<T> &values) 
{
    vector<int> max_ids;
    T max_value = *max_element(values.begin(), values.end());

    for (int i=0;i<values.size();i++)
    {
        if (values[i] == max_value)
        {
            max_ids.push_back(i);
        }
    }

    return max_ids[rand() % max_ids.size()];
}

bool Agent::init_ = false;
bool Agent::caught_ = false;
mutex Agent::class_mutex_ = mutex();

Agent::Agent(shared_ptr<Environment> env, Position pos, int id, shared_ptr<mutex> io_mutex, bool random) : 
    env_{env}, pos_{pos}, id_{id}, random_{random}, io_mutex_{io_mutex}, num_iterations_{0}, last_dist_{0, 0}
{
    q_ = make_unique<vector<vector<vector<short>>>>();
    Position map_size = env_->getSize();
    vector<short> actions(4, 0);
    vector<vector<short>> row(map_size[1]*2, actions);
    for (int x=0; x<(map_size[0]*2); x++)
    {
        q_->push_back(row);
    }

    unique_lock lck(class_mutex_);    
    if (!init_)
    {
        srand((unsigned)time(0)); 
        init_ = true;
    }
    lck.unlock();

    unique_lock io_lck(*io_mutex_);
    cout << "[Agent " << id_ << "]: Initialized successfully" << endl; 
 }

Agent::~Agent()
{
}

void Agent::run()
{
    unique_lock io_lck(*io_mutex_);
    cout << "[Agent " << id_ << "]: Starting to learn now..." << endl; 
    io_lck.unlock();

    pos_ = env_->generatePosition();

    unique_lock lck(class_mutex_);
    num_iterations_ = 0;
    caught_ = 0;

    while (!caught_)
    {
        lck.unlock();
        num_iterations_++;

        int action_id = takeAction();

        // io_lck.lock();
        // cout << "[Agent " << id_ << "]: Took action " << action_id << ", reached position " << pos_ << endl; 
        // io_lck.unlock();

        if (!random_ && last_dist_ != ZERO_POS)
            updateQ(action_id);

        if (env_->caughtTarget(pos_) && !random_)
        {
            lck.lock();
            caught_ = true;
            lck.unlock();
            io_lck.lock();
            cout << "[Agent " << id_ << "]: Caught the target at position " << pos_ << " after " << num_iterations_ << " iterations" << endl;
            return;
        }

        this_thread::sleep_for(std::chrono::milliseconds(1000));
        lck.lock();
    }
}

int Agent::takeAction()
{
    int action_id;
    vector<short> action_values(4, 0);

    if (!random_)
    {
        action_values = (*q_)[pos_[0]][pos_[1]];
    }

    updateActionValues(action_values);
    action_id = randMaxElement<short>(action_values);
    pos_ += Actions[action_id];

    return action_id;    
}

void Agent::updateQ(int action_id)
{
    auto dist = env_->getTargetPosition() - pos_ + (env_->getSize() - 1);

    if (env_->caughtTarget(pos_))
    {
        (*q_)[last_dist_[0]][last_dist_[1]][action_id] = REWARD_CATCH;
    }
    else
    {
        (*q_)[last_dist_[0]][last_dist_[1]][action_id] = 
        REWARD_TIME + G * (*max_element((*q_)[last_dist_[0]][last_dist_[1]].begin(), 
                            (*q_)[last_dist_[0]][last_dist_[1]].end()));    
    }

    last_dist_ = dist;
}

void Agent::updateActionValues(vector<short> &action_values)
{
    if (pos_[1]+1 >= env_->getSize()[1])    // Up
        action_values[0] = -10;
    if (pos_[1]-1 < 0)    // Down
        action_values[1] = -10;
    if (pos_[0]-1 < 0)    // Left
        action_values[2] = -10;
    if (pos_[0]+1 >= env_->getSize()[0])    // Right
        action_values[3] = -10;
}

Position Agent::getPos()
{
    unique_lock lck(mutex_);
    return pos_;
}

bool Agent::targetCaught()
{
    unique_lock lck(class_mutex_);
    return caught_;
}
