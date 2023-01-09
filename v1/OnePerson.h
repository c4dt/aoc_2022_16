//
// Created by Home on 01.01.23.
//

#ifndef AOC_2022_16_ONEPERSON_H
#define AOC_2022_16_ONEPERSON_H


#include <utility>

#include "NumericVector.h"
#include "Tunnels.h"

class OnePerson {
    Tunnels base;
public:
    explicit OnePerson(Tunnels base) : base(std::move(base)) {}

    static unsigned param_len() { return 30; }

    [[nodiscard]] unsigned param_values() const { return 2 * base.fact; }

    unsigned calc_fitness(NumericVector route);
};


#endif //AOC_2022_16_ONEPERSON_H
