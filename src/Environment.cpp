#include "Environment.h"


bool Environment::init_ = false;

Environment::Environment(shared_ptr<mutex> io_mutex, int size_x, int size_y): io_mutex_{io_mutex}, size_{size_x, size_y} 
{
    if (!init_)
    {
        srand((unsigned)time(0)); 
        init_ = true;
    }
}

void Environment::loadMapFromFile(string file_name) 
{
    fstream fstr(file_name);
    string line;

    while (getline(fstr, line))
    {
        istringstream sline(line);
        short n;
        char c;
        vector<short> row;
        while (sline >> n >> c && c == ',') 
        {
            row.push_back(n);
        }
        map_->push_back(row);
    }
}

void Environment::visualize(int rate, bool reset_cursor_pos) 
{
    vector<Position> agents_pos(agents_.size());
    Position target_pos;
    string cell_value = "🞎";
    unique_lock lck(mutex_, defer_lock);
    unique_lock io_lck(*io_mutex_, defer_lock);
    bool first_time = true;

    bool target_caught = false;

    this_thread::sleep_for(chrono::seconds(rate));

    while(!target_caught)
    {
        target_caught = Agent::targetCaught();

        lck.lock();
        // Retrieve positions of all agents including the target
        for (int a=0; a<agents_.size(); a++)
        {
            agents_pos[a] = agents_[a].lock()->getPos();
        }
        target_pos = target_.lock()->getPos();
        lck.unlock();


        io_lck.lock();

        // Reset cursor position
        if (!first_time && reset_cursor_pos)
            for (int y=size_[1]+1; y>=0; y--)
                std::cout << "\033[F\r";

        // Print map
        for (int y=size_[1]-1; y>=0; y--)
        {
            // Print y-axis values
            cout << "\t" << y;

            for (int x=0; x<size_[0]; x++)
            {
                // Set default value to empty cell
                cell_value = CellState::free;

                // Set value to police car if an agent is on this cell
                for (int a=0; a<agents_pos.size(); a++)
                    if (agents_pos[a][0] == x && agents_pos[a][1] == y)
                        cell_value = CellState::agent;

                // Set value to car if the target is on this cell
                if (target_pos[0] == x && target_pos[1] == y)
                    cell_value = CellState::target;

                cout << "\t" << cell_value;
            }
            cout << endl;
        }

        // Print x-axis values
        cout << "\t";
        for (int x=0; x<size_[0]; x++)
            cout << "\t" << x;
        cout << endl << endl;

        io_lck.unlock();

        first_time = false;

        this_thread::sleep_for(chrono::seconds(rate));
    }
}

void Environment::addAgent(weak_ptr<Agent> agent)
{
    agents_.emplace_back(agent);
} 

// void Environment::createAgents(int number_agents) 
// {
//     for (int i=0; i<number_agents; i++)
//     {
//         Position new_pos = generatePosition();
//         agents_.emplace_back(make_unique<Agent>(shared_ptr<Environment>(this), new_pos));
//     }
// }

bool Environment::posInBoundaries(const Position &pos)
{
    return pos >= ZERO_POS && pos < size_;
}

bool Environment::caughtTarget(const Position &pos)
{
    unique_lock lck(mutex_);
    auto tmp_target = target_.lock();
    return tmp_target->pos_ == pos;
}

Position Environment::getTargetPosition()
{
    unique_lock lck(mutex_);
    auto tmp_target = target_.lock();
    return tmp_target->getPos();
}

Position Environment::getSize()
{
    unique_lock lck(mutex_);
    return size_;
}

void Environment::setTarget(weak_ptr<Agent> target)
{
    target_ = target;
}

Position Environment::generatePosition()
{
    return Position(rand()%size_[0], rand()%size_[1]);
}