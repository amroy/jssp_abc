//
// Created by amroy on 1/22/20.
//

#include "jssp.h"

//JSSP::JSSP() : Problem() {}

void JSSP::loadInstance(const std::string &data_source) {
    // Read problem instance from the data source
    std::ifstream fs;
    std::string line;

    try {
        fs.open(data_source);
        getline(fs, line);
        getline(fs, line);
        std::string svalue; // single value
        std::istringstream ls(line);
        getline(ls, svalue, ' ');
        M = std::stoi(svalue);
        getline(ls, svalue, ' ');
        N = std::stoi(svalue);
        dimension = M*N;

        machines.reserve(N);
        durations.reserve(N);

        int i=0;
        while(getline(fs, line)) {
            std::istringstream ls(line);
            std::vector<int> durations_;
            for(int j=0; i<M; ++j) {
                getline(ls, svalue, ' ');
                int operation = std::stoi(svalue);
                machines[i].push_back(operation);
                getline(ls, svalue, ' ');
                durations_.push_back(std::stoi(svalue));
            }
            i++;
        }
    } catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

std::vector<std::vector<int>> JSSP::getMachines() const {
    return machines;
}

std::vector<std::vector<int>> JSSP::getDurations() const {
    return durations;
}

int JSSP::getNumberOfMachines() const {
    return M;
}

int JSSP::getNumberOfTasks() const {
    return N;
}

JSSP::~JSSP() {

}