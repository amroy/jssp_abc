#include "solution.h"

Solution::Solution() {
    elements.reserve(problem->getDimension());
}

Solution::Solution(std::shared_ptr<Problem> p) : problem(p) {}

int Solution::evaluate() {
    std::vector<std::vector<int>> tasks_ends;
    std::vector<int> occurences;
    int i=0, j=0, job=0, machine1=0, machine2=0, end1=0, end2=0;
    auto D = problem->getDimension();
    std::shared_ptr<JSSP> jssp_problem = std::dynamic_pointer_cast<JSSP>(problem);
    const auto machines = jssp_problem->getMachines();
    const auto durations = jssp_problem->getDurations();
    int M = jssp_problem->getNumberOfMachines();

    for(i=0; i<D; ++i) {
        job = elements[i];
        for(j=0; j<i; ++j) {
            if(elements[j] == job)
                occurences[i]++;
        }
    }

    for(i=0; i<D; ++i) {
        machine1 = machines[elements[i]][occurences[i]];
        if(occurences[i] == 0) {
            tasks_ends[machine1][i] += durations[elements[i]][occurences[i]];
            j = i-1;
            while(j>=0) {
                if(tasks_ends[machine1][j] == 0)
                    j--;
                else {
                    tasks_ends[machine1][i] += tasks_ends[machine1][j];
                    break;
                }
            }
        } else {
            machine2 = machines[elements[i]][occurences[i]-1];
            end1 = end2 = 0;
            tasks_ends[machine1][i] += durations[elements[i]][occurences[i]];
            j = i-1;
            while(j>=0) {
                if(tasks_ends[machine2][j]>0 && elements[j]==elements[i] && occurences[i]-occurences[j]==1) {
                    end1 = tasks_ends[machine2][j];
                    break;
                } else {
                    j--;
                }
            }

            j = i-1;
            while(j>=0) {
                if(tasks_ends[machine1][j] == 0)
                    j--;
                else {
                    end2 = tasks_ends[machine1][j];
                    break;
                }
            }

            tasks_ends[machine1][i] = std::max<int>(end1, end2);
        }
    }

    // Compute cmax
    int cmax = 0;
    for(i=0; i<M; ++i) {
        j = D-1;
        while(j>=0) {
            if(tasks_ends[i][j] > 0) {
                if(tasks_ends[i][j] >= cmax)
                    cmax = tasks_ends[i][j];
                break;
            } else {
                j--;
            }
        }
    }

    // Objective function value
    this->value = cmax;

    return cmax;
}

void Solution::invert() {
    double r1{0.0}, r2{0.0};
    int D = problem->getDimension(), ir1{0}, ir2{0};

    do {
        r1 = (random() * 32767.0) / (32767.0+1);
        r2 = (random() * 32767.0) / (32767.0+1);
        ir1 = int(r1*D);
        ir2 = int(r2*D);
    } while(abs(ir1-ir2) < 2);

    auto tmp{this->elements[0]};
    for (int i = 0; i < ir2 - ir1/2; ++i) {
        tmp = this->elements[ir1+i];
        this->elements[ir1+i] = this->elements[ir2-i];
        this->elements[ir2-i] = tmp;
    }

    update();
}

void Solution::insert() {
    double r1{0.0}, r2{0.0};
    int D = problem->getDimension(), ir1{0}, ir2{0};

    do {
        r1 = (random() * 32767.0) / (32767.0+1);
        r2 = (random() * 32767.0) / (32767.0+1);
        ir1 = int(r1*D);
        ir2 = int(r2*D);
    } while(ir1<ir2);

    for (int i = ir1; i < ir2; ++i) {
        if (i == ir2-1)
            this->elements[i] = this->elements[ir1];
        else {
            this->elements[i] = this->elements[i+1];
        }
    }

    update();
}

void Solution::swap() {
    double r1{0.0}, r2{0.0};
    int D = problem->getDimension(), ir1{0}, ir2{0};

    do {
        r1 = (random() * 32767.0) / (32767.0+1);
        r2 = (random() * 32767.0) / (32767.0+1);
        ir1 = int(r1*D);
        ir2 = int(r2*D);
    } while(ir1==ir2);

    auto tmp = this->elements[ir1];
    this->elements[ir1] = this->elements[ir2];
    this->elements[ir2] = tmp;

    update();
}

void Solution::swap(int i, int j) {
    auto tmp = this->elements[i];
    this->elements[i] = this->elements[j];
    this->elements[j] = tmp;

    this->update();
}

int& Solution::operator[](int i) {
    return elements[i];
}

void Solution::update() {
    this->evaluate();
    this->_computeFitness();
}

void Solution::_computeFitness() {
    this->fitness = value > 0 ? 1 / (value + 1) : 1 + fabs(value);
}

void Solution::incrementTrials() {
    this->trials++;
}

void Solution::resetTrials() {
    this->trials = 0;
}