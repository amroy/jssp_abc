#include "bee_colony.h"

BeeColonyAlgorithm::BeeColonyAlgorithm(std::shared_ptr<Problem> p) : problem{p} {

}

void BeeColonyAlgorithm::initFoodSource(int index) {

}

void BeeColonyAlgorithm::initialize() {
    for (int i=0; i<food_number; ++i)
        initFoodSource(i);

    auto& first_food = food_sources[0];
    global_min = first_food->getValue();
    for(int i=0; i<problem->getDimension(); ++i)
        global_params[i] = (*first_food)[i];

}

void BeeColonyAlgorithm::saveBestScore() {
    int D = problem->getDimension();
    for (auto& food : food_sources) {
        if(food.getFitness() < global_min) {
            global_min = food.getFitness();
            for (int j = 0; j < D; ++j) {
                global_params[j] = food[j];
            }
        }
    }
    pairWiseBasedLocalSearch();
}

void BeeColonyAlgorithm::computeProbabilities() {
    double maxfit = food_sources[0].getFitness();
    for (auto& food : food_sources) {
        if(food.getFitness() > maxfit)
            maxfit = food.getFitness();
    }

    for (auto& food : food_sources) {
        food.setProbability(0.9*(food.getFitness()/maxfit) + 0.1);
    }
}

void BeeColonyAlgorithm::sendEmployedBees() {
    int i{0};
    for (auto& food : food_sources) {
        Solution new_sol{std::move(fastLocalSearch(i))};
        if(new_sol.getFitness() > food.getFitness()) {
            new_sol.resetTrials();
            food = std::move(new_sol);
        } else {
            food.incrementTrials();
        }
    }
}

void BeeColonyAlgorithm::sendScoutBees() {
    int max_trial_index{0};
    int max_trials{0};
    int i{0};
    for (const auto& food : food_sources) {
        if(food.trials > max_trials)
            max_trial_index = i;
        ++i;
    }
    if(max_trials >= limit)
        initFoodSource(max_trial_index);
}

void BeeColonyAlgorithm::sendOnLookerBees() {
    int i{0};
    auto iter = food_sources.begin();
    while(iter != food_sources.end()) {
        double r = (random() * 32767.0) / (32767.0+1);
        auto new_sol{std::move(fastLocalSearch(i))};
        if(new_sol.getFitness() > iter->getFitness()) {
            new_sol.resetTrials();
            *iter = std::move(new_sol);
        } else {
            iter->incrementTrials();
        }
    }
}

Solution BeeColonyAlgorithm::pairWiseBasedLocalSearch() {
    int i{0}, j{0}, D{problem->getDimension()};
    Solution tmp_solution{best_food_source};

    while(i<D-1 && j<D) {
        tmp_solution.swap(i, j);
        if(tmp_solution.getFitness() > best_food_source.getFitness()) {
            best_food_source = tmp_solution;
        }
        ++i;
        ++j;
    }
}

Solution BeeColonyAlgorithm::fastLocalSearch(int index) {
    int D{problem->getDimension()};
    Solution next_sol{food_sources[index]};
    Solution best_sol;
    double best_fitness{0.0};

    for (int i = 0; i < (D - 1) * (D - 2); ++i) {
        double q = (random() * 32767.0) / (32767.0+1);
        if (q<prs) {
            next_sol.swap();
        } else if (q>=prs && q<=prs+pri) {
            next_sol.insert();
        } else if (q>=(prs+pri) && q<=(prinv+prs+pri)) {
            next_sol.invert();
        }
        if(next_sol.getFitness() > best_fitness) {
            best_fitness = next_sol.getFitness();
            best_sol = next_sol;
        }
    }

    return best_sol;
}

std::shared_ptr<Problem> BeeColonyAlgorithm::getProblem() const {
    return problem;
}

void BeeColonyAlgorithm::run() {
    while(this->is_running) {
        for (int run=0; run<max_iter; ++run) {
            initialize();
            saveBestScore();
            for (int iter = 0; iter < max_cycle; ++iter) {
                sendEmployedBees();
                computeProbabilities();
                sendOnLookerBees();
                saveBestScore();
                sendScoutBees();
                progress += 100.0/max_cycle;
            }

            global_mins.push_back(global_min);
        }
    }

    is_running = false;
}
