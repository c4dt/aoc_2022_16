//
// Created by Home on 01.01.23.
//

#include "Tunnels.h"
#include <utility>
#include <sstream>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Splits a string by a given delimiter and returns the vector of strings.
// https://stackoverflow.com/a/46931770/1573347
vector<string> split(const string &s, const string &delimiter, unsigned max_matches = -1) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos && res.size() + 1 < max_matches) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

Tunnels::Tunnels(const string &file) {
    string line;
    ifstream infile(file);
    while (getline(infile, line)) {
        if (line.empty()) {
            break;
        }
        add_valve(line);
    }
    size_t valves_max = 0;
    for (auto const &link: links) {
        valves_max = max(link.second.size(), valves_max);
    }
    fact = 1;
    for (unsigned i = 1; i <= valves_max; ++i){
        fact *= i;
    }
}

void Tunnels::add_valve(const string &line) {
    auto first = split(line, "; ");
    auto left = split(first.at(0), " ");
    auto right = split(first.at(1), " ", 5);
    auto rate = split(left.at(4), "=");
    auto valve = left.at(1);

    valves.push_back(valve);
    rates[valve] = stoul(rate.at(1));
    links[valve] = split(right.at(4), ", ");
}


unsigned Tunnels::calc_rate(const vector<Visit> &tour, unsigned length) {
    unsigned total_rate = 0;
    for (auto const &step: tour) {
        if (length < 2) {
            break;
        }
        --length;
        if (step.open) {
            total_rate += rates[step.valve] * length--;
        }
    }
    return total_rate;
}

Visit Tunnels::get_visit(const string &current, unsigned index) {
    return Visit{valves.at(index % links[current].size()), index >= fact};
}

std::ostream &operator<<(std::ostream &out, const Tunnels &t) {
    out << "Number of valves: " << t.valves.size() << " - Factorial: " << t.fact;
    return out;
}

vector<Visit> str_to_tour(string s) {
    vector<Visit> ret;
    for (auto const &step: split(s, " ")) {
        ret.emplace_back(Visit{string(step, 0, 2), step.size() > 2});
    }
    return ret;
}

void test_tunnels() {
    assert(split("one two three", " ").size() == 3);
    assert(split("one two three", " ", 1).size() == 1);
    assert(split("one two three", " ", 2).size() == 2);
    assert(split("one two three", " ", 3).size() == 3);
    Tunnels sample("../sample-input.txt");
    unsigned rate = sample.calc_rate(str_to_tour("AA DD_ CC BB_ AA II JJ_ II AA DD EE FF GG HH_ GG FF EE_ DD CC_"), 30);
    assert(rate == 1651);
}