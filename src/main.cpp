#include <iostream>

#include "Manager.h"

int main() {

    Manager man;
    man.createAgents(5, 15, 10);
    man.runLearning(5, true);

    std::cout << "Hello World!" << "\n";
    return 0;
}