//
// Created by Home on 01.01.23.
//

#ifndef AOC_2022_16_TWOPERSONS_H
#define AOC_2022_16_TWOPERSONS_H

#include <utility>

#include "NumericVector.h"
#include "Tunnels.h"

class TwoPersons {
    Tunnels base;
public:
    explicit TwoPersons(Tunnels base) : base(std::move(base)) {}

    static unsigned param_len() { return 52; }

    [[nodiscard]] unsigned param_values() const { return 2 * base.fact; }

    unsigned calc_fitness(NumericVector route);
};

#endif //AOC_2022_16_TWOPERSONS_H
