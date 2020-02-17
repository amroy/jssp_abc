//
// Created by amroy on 1/25/20.
//

#ifndef JSSP_PROBLEM_H
#define JSSP_PROBLEM_H

#include <vector>
#include <string>
#include <memory>

class Solution;
class Problem {
public:
    Problem();
    Problem(const Problem&);
    Problem(Problem&&);

    virtual void loadInstance(const std::string&) = 0;
    int getDimension() const;
    std::shared_ptr<Solution> getBestSolution() const;
    void setBestSolution(Solution&&);

    virtual ~Problem() = default;

    std::vector<Solution*> solutions;
protected:
    std::string name;
    std::weak_ptr<Solution> best_solution;
    int dimension{0};
};
#endif //JSSP_PROBLEM_H
