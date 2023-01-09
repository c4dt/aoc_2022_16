//
// Created by Home on 03.01.23.
//

#ifndef AOC_2022_16_ROUTE_H
#define AOC_2022_16_ROUTE_H

#include <vector>
#include <string>

struct Visit {
    std::string valve;
    bool open;
};

struct Route {
    std::vector<Visit> visits;
    unsigned rate;

    [[nodiscard]] std::vector<int> valve_positions(const std::string &valve) const;

    std::vector<std::string> get_valves() const;
};

std::ostream &operator<<(std::ostream &out, const Route &t);

#endif //AOC_2022_16_ROUTE_H
