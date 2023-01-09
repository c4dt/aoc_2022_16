//
// Created by Home on 01.01.23.
//

#include "OnePerson.h"
#include <set>
#include <string>

using namespace std;

unsigned OnePerson::calc_fitness(NumericVector route) {
    set<string> opened;
    string valve = "AA";
    vector<Visit> tour{Visit{valve, false}};
    for (auto const &step: route.get_values()) {
        auto valves = base.links[valve];
        valve = valves.at(step % valves.size());
        bool open = base.rates[valve] > 0 && step >= base.fact && opened.insert(valve).second;
        tour.emplace_back(Visit{valve, open});
    }
    return base.calc_rate(tour, param_len());
}
