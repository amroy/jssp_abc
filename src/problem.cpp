//
// Created by amroy on 1/25/20.
//

#include "problem.h"

Problem::Problem() {}

std::shared_ptr<Solution> Problem::getBestSolution() const {
    return best_solution.lock();
}

int Problem::getDimension() const {
    return dimension;
}
