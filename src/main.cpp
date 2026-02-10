#include <iostream>

#include "Manager.h"

int main() {

    Manager man;
    man.createAgents(1, 15, 10);
    man.runLearning(100000, false);

    return 0;
}