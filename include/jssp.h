//
// Created by amroy on 1/22/20.
//

#ifndef JSSP_JSSP_H
#define JSSP_JSSP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>
#include "solution.h"
#include "problem.h"

class JSSP : public Problem {
public:
    //JSSP();
    void loadInstance(const std::string&) override ;
    int getNumberOfMachines() const;
    int getNumberOfTasks() const;
    std::vector<std::vector<int>> getMachines() const;
    std::vector<std::vector<int>> getDurations() const;
    ~JSSP() override;

protected:
    std::vector<std::vector<int>> machines;
    std::vector<std::vector<int>> durations;

    /**
     * Number of machines
     */
    int M = 0;

    /**
     * Number of tasks
     */
    int N = 0;
};

#endif //JSSP_JSSP_H
