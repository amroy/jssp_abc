#include <iostream>
#include <memory>
#include "bee_colony.h"
#include "jssp.h"

int main() {
    std::shared_ptr<Problem> problem{new JSSP()};

    std::string instance_path = "./data/sample_instance.txt";
    problem->loadInstance(instance_path);

    BeeColonyAlgorithm bee_colony{problem};
    bee_colony.run();

    auto best_solution{problem->getBestSolution()};

    return 0;
}