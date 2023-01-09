//
// Created by Home on 01.01.23.
//

#include "TwoPersons.h"
#include <set>

using namespace std;

Visit add_step(Tunnels &base, set<string> &opened, string &valve, unsigned step){
    auto valves = base.links[valve];
    valve = valves.at(step % valves.size());
    bool open = step >= base.fact && opened.insert(valve).second;
    return Visit{valve, open};
}

unsigned TwoPersons::calc_fitness(NumericVector route) {
    set<string> opened;
    string valve1 = "AA";
    string valve2 = "AA";
    vector<Visit> tour1{Visit{valve1, false}};
    vector<Visit> tour2{Visit{valve2, false}};
    bool visit1 = true;
    for (auto const &step: route.get_values()) {
        if (visit1) {
            tour1.push_back(add_step(base, opened, valve1, step));
        } else {
            tour2.push_back(add_step(base, opened, valve2, step));
        }
        visit1 = !visit1;
    }
    return base.calc_rate(tour1, param_len() / 2) + base.calc_rate(tour2, param_len() / 2);
}
