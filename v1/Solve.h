//
// Created by Home on 01.01.23.
//

#ifndef AOC_2022_16_SOLVE_H
#define AOC_2022_16_SOLVE_H


#include <vector>
#include "Tunnels.h"
#include "NumericVector.h"

template<typename T>
class Solve {
    T input;
    std::vector<NumericVector> best;

    void init_best(size_t length);

    NumericVector random();

public:
    Solve(const T &input): input(input){}

    unsigned run_random(unsigned n);

    unsigned run_annealing(unsigned n, double p_keep_worse);

    unsigned run_genetic(unsigned n, size_t population, size_t random, double p_mutate);

    unsigned get_best();
};

#include "Solve.tpp"

#endif //AOC_2022_16_SOLVE_H
