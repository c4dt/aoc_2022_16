//
// Created by Home on 01.01.23.
//

#include "OnePerson.h"
#include <string>
#include <algorithm>
#include <random>
#include <iostream>
#include <set>

using namespace std;

Route OnePerson::get_random() {
    return base.calc_route(vector<Visit>(), param_len());
}

map<string, vector<int>> multi_valves(const Route &r) {
    random_device rand;
    default_random_engine e1(rand());
    auto valves = r.get_valves();
    shuffle(valves.begin(), valves.end(), e1);
    map<string, vector<int>> positions;
    for (auto const &valve: valves) {
        auto positions_tmp = r.valve_positions(valve);
        if (positions_tmp.size() > 1) {
            positions[valve] = positions_tmp;
        }
    }
    return positions;
}

vector<int> one_multi_valve(const Route &r) {
    auto positions = multi_valves(r);
    if (positions.empty()) {
        return {};
    }
    return positions.begin()->second;
}

pair<int, int> get_range(vector<int> positions) {
    random_device rand;
    default_random_engine e1(rand());

    auto length = int(positions.size());
    int start = uniform_int_distribution<int>(0, length - 2)(e1);
    int stop = uniform_int_distribution<int>(start + 1, length - 1)(e1);

    return {positions.at(start), positions.at(stop)};
}

Route OnePerson::get_mutation(const Route &r) {
    vector<int> positions = one_multi_valve(r);
    int occurrences = int(positions.size());
    if (occurrences == 0) {
        return r;
    }
    auto range = get_range(positions);
    auto start = range.first;
    auto stop = range.second;

    vector<Visit> new_r = r.visits;
    new_r.erase(new_r.begin() + start + 1, new_r.begin() + stop + 1);
    set<string> opened;
    for (auto const &v: new_r) {
        if (v.open) {
            opened.insert(v.valve);
        }
    }

    vector<Visit> new_visit{new_r.at(start)};
    do {
        Visit v = base.random_visit(new_visit.back().valve);
        if (v.open) {
            v.open = opened.insert(v.valve).second;
        }
        new_visit.push_back(v);
    } while (new_visit.back().valve != new_r.at(start).valve);
    new_r.insert(new_r.begin() + start + 1, new_visit.begin(), new_visit.end());

    return base.calc_route(new_r, param_len());
}

Route OnePerson::get_crossover(const Route &r1, const Route &r2) {
    random_device rand;
    default_random_engine e1(rand());

    vector<int> positions;
    for (int i = 1; i < param_len(); ++i) {
//        auto links = base.links[r1.visits.at(i-1).valve];
//        if (find(links.begin(), links.end(), r2.visits.at(i).valve) != links.end()) {
        if (r1.visits.at(i).valve == r2.visits.at(i).valve){
            positions.push_back(i);
        }
    }
    if (positions.empty()) {
        return r1;
    }

    int cut = positions[uniform_int_distribution<int>(0, int(positions.size()) - 1)(e1)];
    auto v3 = r1.visits;
    v3.erase(v3.begin() + cut, v3.end());
    v3.insert(v3.end(), r2.visits.begin() + cut, r2.visits.end());

    return base.calc_route(v3, param_len());
}

Route get_crossover_2(const Route &r1, const Route &r2) {
    random_device rand;
    default_random_engine e1(rand());

    auto valves_r1 = multi_valves(r1);
    auto valves_r2 = multi_valves(r2);
    for (auto const &valves: valves_r1) {
        auto positions_r2 = valves_r2.find(valves.first);
        if (positions_r2 != valves_r2.end()) {
            auto range1 = get_range(valves.second);
            auto range2 = get_range(positions_r2->second);
//            cout << "Range 1: " << range1.first << ":" << range1.second << endl;
//            cout << "Range 2: " << range2.first << ":" << range2.second << endl;
//            cout << "r1: " << r1 << endl;
//            cout << "r2: " << r2 << endl;
            vector<Visit> v3 = r1.visits;
            v3.erase(v3.begin() + range1.first + 1, v3.begin() + range1.second);
            v3.insert(v3.begin() + range1.first + 1, r2.visits.begin() + range2.first + 1,
                      r2.visits.begin() + range2.second);
//            auto r3 = base.calc_route(v3, param_len());
////            cout << "r3: " << r3 << endl;
//            return r3;
        }
    }

    return r1;
}

void test_oneperson() {
    auto t = Tunnels("../sample-input.txt");
    auto op = OnePerson(t);
    auto r1 = op.get_random();
    assert(r1.visits.size() == op.param_len());

    unsigned differences = 0;
    for (int i = 0; i < 100; i++) {
        auto r2 = op.get_mutation(r1);
        assert(r2.visits.size() == op.param_len());
        assert(r1.visits.front().valve == r2.visits.front().valve);
        for (size_t pos = 0; pos < OnePerson::param_len(); ++pos) {
            if (r1.visits.at(pos).valve != r2.visits.at(pos).valve) {
                ++differences;
            }
        }
    }
    assert(differences >= 100);

    differences = 0;
    auto r2 = op.get_random();
    for (int i = 0; i < 100; i++) {
        auto r3 = op.get_crossover(r1, r2);
        assert(r3.visits.size() == op.param_len());
//        cout << "R1: " << r1 << endl;
//        cout << "R2: " << r2 << endl;
//        cout << "R3: " << r3 << endl;
        assert(r3.visits.front().valve == r1.visits.front().valve);
        for (size_t pos = 0; pos < OnePerson::param_len(); ++pos) {
            if (r1.visits.at(pos).valve != r2.visits.at(pos).valve) {
                ++differences;
                break;
            }
        }
    }
    assert(differences >= 100);

    //    cout << "Differences for 100 mutations are: " << differences << endl;
}
