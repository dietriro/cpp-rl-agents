#include <iostream>

#include "Manager.h"

int main() {

    Manager man;
    man.createAgents(1, 20, 15);
    man.runLearning(100, false);

    std::cout << "Hello World!" << "\n";
    return 0;
}