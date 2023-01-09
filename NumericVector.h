//
// Created by Home on 01.01.23.
//

#ifndef AOC_2022_16_NUMERICVECTOR_H
#define AOC_2022_16_NUMERICVECTOR_H

#include <utility>
#include <vector>
#include <random>
#include "Tunnels.h"

void testNumeric();

class NumericVector {
    std::vector<unsigned> values;
    unsigned length;
    unsigned value_max;
    unsigned fitness = -1;

    void randomize();

    friend void testNumeric();

public:
    NumericVector(unsigned length, unsigned value_max, std::vector<unsigned> values = std::vector<unsigned>()) : length(
            length), value_max(value_max), values(std::move(values)) {
        randomize();
    }

    NumericVector mutate();

    NumericVector crossover(const NumericVector &other);

    unsigned get_fitness() const;
    void set_fitness(unsigned fit);

    std::vector<unsigned> get_values();
};

#endif //AOC_2022_16_NUMERICVECTOR_H
