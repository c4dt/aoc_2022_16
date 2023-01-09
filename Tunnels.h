//
// Created by Home on 01.01.23.
//

#ifndef AOC_2022_16_TUNNELS_H
#define AOC_2022_16_TUNNELS_H

#include <vector>
#include <string>
#include <map>
#include "Route.h"

struct Tunnels {
    std::vector<std::string> valves;
    std::map<std::string, unsigned> rates;
    std::map<std::string, std::vector<std::string>> links;
    unsigned fact;

    Tunnels(const std::string& input);

    Visit get_visit(const std::string& current, unsigned index);
    Route calc_route(std::vector<Visit> tour, unsigned length);
    Visit random_visit(const std::string &current);

private:
    void add_valve(const std::string& line);
};

std::ostream &operator<<(std::ostream &out, const Tunnels &t);

void test_tunnels();

#endif //AOC_2022_16_TUNNELS_H
