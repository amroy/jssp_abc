#ifndef JSSP_ABC_BEECOLONYALGORITHM_H
#define JSSP_ABC_BEECOLONYALGORITHM_H


#include <vector>
#include <math.h>
#include <memory>
#include "problem.h"
#include "solution.h"

constexpr double fitness_value(double val) { return val > 0 ? 1 / (val + 1) : 1 + fabs(val); }

class BeeColonyAlgorithm {
public:
    BeeColonyAlgorithm() = default;

    explicit BeeColonyAlgorithm(std::shared_ptr<Problem>);

    BeeColonyAlgorithm(BeeColonyAlgorithm &) = delete;

    BeeColonyAlgorithm &operator=(const BeeColonyAlgorithm &) = delete;

    /**
     * Initialize all food sources
     */
    void initialize();

    /**
     * Initialize a single food source
     */
    void initFoodSource(int);

    void saveBestScore();
    
    /** A food source is chosen with the probability which is proportioal to its quality
	 * Different schemes can be used to calculate the probability values
	 * For example prob(i)=fitness(i)/sum(fitness)
	 * or in a way used in the metot below prob(i)=a*fitness(i)/max(fitness)+b
	 * probability values are calculated by using fitness values and normalized by dividing maximum fitness value
     */
    void computeProbabilities();

    
    void sendEmployedBees();

    /**
     * Determine the food sources whose trial counter exceeds the "limit" value. In Basic ABC, 
     * only one scout is allowed to occur in each cycle
     */
    void sendOnLookerBees();

    void sendScoutBees();

    Solution pairWiseBasedLocalSearch();

    Solution fastLocalSearch(int);

    void run();

    std::shared_ptr<Problem> getProblem() const;

    ~BeeColonyAlgorithm() = default;

private:
    /**
     * The number of colony size (employed bees+onlooker bees)
     */
    int colony_size = 20;

    /**
     * The number of food sources equals the half of the colony size
     */
    int food_number = colony_size / 2;

    /**
     * A food source which could not be improved through "limit" trials is abandoned by its employed bee
     */
    int limit = 20;

    /**
     * The number of cycles for foraging {a stopping criteria}
     */
    int max_cycle = 150;

    /**
     * Fast local search probabilities
     */
    double prs = 0.3;
    double pri = 0.5;
    double prinv = 1;

    /**
     * Algorithm can be run many times in order to see its robustness
     */
    int max_iter = 30;

    /**
     * Foods is the population of food sources. Each row of Foods matrix is a vector holding D parameters to be optimized.
     * The number of rows of Foods matrix equals to the FoodNumber
     */
    std::vector<Solution> food_sources;

    Solution best_food_source{nullptr};

    /**
     * The problem beeing optimized
     */
    std::shared_ptr<Problem> problem{nullptr};

    /**
     * The best solution score found so far
     */
    double global_min{0};

    /**
     * The global solution values
     */
    std::vector<int> global_params;

    /**
     * The global mins found at each runtime
     */
    std::vector<double> global_mins;

    bool is_running = false;

    double progress{0};

};


#endif //JSSP_ABC_BEECOLONYALGORITHM_H
