#ifndef JSSP_ABC_ALGORITHM_H
#define JSSP_ABC_ALGORITHM_H

#include "problem.h"

class Algorithm {
public:
    Algorithm() = default;
    explicit Algorithm(Problem*);
    virtual ~Algorithm() = default;
    virtual void run() = 0;

protected:
    std::string name;
    Problem* problem{nullptr};
};

#endif
