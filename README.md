# CPPND: ParralRL

## Description

This is the final project I implemented for the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). 

The goal of it is to have multiple Reinforcement Learning agents running around in a 2D gridworld chasing a single target. The agents learn to follow the target using Q-Learning with the xy-distance forming the state space and the actions being up, down, left and right. Each agent is started in a single thread as well as the target. They move autonomously in the environment and as soon as one of the agents catches the target, the run is ended (all threads are terminated except for main). 

Of course multiple runs are needed in order for the agents to learn something. A negative reward of -2 is used per timestep for not catching the target and a positive reward of 100 is used for actually catching the target. A map of the environment can be printed on the screen in order to visualize the catching, this however requires a significant wait time for the agents because the map would otherwise update too fast.


## Code Overview

The code consists of 4 different classes: Manager, Environment, Agent and Position. The Manager is the top level class, managing all threads. It is created from main, where the user can specify the number of agents as well as the number of runs the program should perform (one run is from start until the target is catched). After each run the Manager start new threads for each agent as well as the target, hence resetting previous positions to random values. Additionally the Manager can also start a thread for visualization using a method from Environment, where the map is visualized including all agents and the target, however, this is only recommended when a significant sleep is specified in the agents *run* method.

As already described, the Agent class provides functionality for taking actions in the environment and learning a Q-function based on the rewards received. The core of the Agent is the *run* function, which is called by each thread. The Agent class is not only used for the RL-Agents but also for the target, since most of the functionality is the same here. Each Agent keeps a pointer to the environment, where it can receive information about the targets position as well as the size of the environment. 

The Environment class keeps weak pointers to the agents as well in order to visualize them properly. 


## Addressed Rubric Points

The following points from the [required rubrics](https://review.udacity.com/#!/rubrics/2533/view) were being addressed in this project:

### Loops, Functions, I/O

- The project demonstrates an understanding of C++ functions and control structures.


### Object Oriented Programming

- The project uses Object Oriented Programming techniques.
- Classes use appropriate access specifiers for class members.
- Class constructors utilize member initialization lists.
- Classes encapsulate behavior.
- Templates generalize functions in the project.

### Memory Management

- The project makes use of references in function declarations.
- The project uses scope / Resource Acquisition Is Initialization (RAII) where appropriate.
- The project uses move semantics to move data, instead of copying it, where possible.
- The project uses smart pointers instead of raw pointers.

### Concurrency

- The project uses multithreading.
- A mutex or lock is used in the project.


## Future Work

There are a lot of things that could improve this project further, a few are mentioned below:

- Load a map from the environment and include obstacles
- Have a shared Q-function which is updated from all Agents simultaneuosly


## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)


## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./ParralRL`.
