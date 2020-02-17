#ifndef JSSP_ABC_SOLUTION_H
#define JSSP_ABC_SOLUTION_H

#include <vector>
#include <memory>
#include <math.h>
#include "problem.h"

class Problem;
class Solution {
public:
    Solution();
    Solution(std::shared_ptr<Problem>);
    Solution(const Solution&) = default;
    Solution(Solution&&) = default;
    Solution& operator=(const Solution&) = default;
    Solution& operator=(Solution&&) = default;
    virtual ~Solution() = default;

    int& operator[](int);

    void invert();
    void insert();
    void swap();
    void swap(int, int);

    void update();

    double getFitness() const;
    void setFitness(double);
    double getValue() const;
    void setValue(double);
    double getProbability() const;
    void setProbability(double);

    void incrementTrials();
    void resetTrials();

    int trials{0};

    virtual int evaluate();

private:
    void _computeFitness();
    void _computeProbabilities();

protected:
    std::vector<int> elements;
    double fitness{0.0};
    double value{0.0};
    double probability{0.0};

    std::shared_ptr<Problem> problem;
};

#endif
