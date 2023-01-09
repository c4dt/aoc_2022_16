//
// Created by Home on 03.01.23.
//

#include "Route.h"
#include <iostream>

using namespace std;

vector<int> Route::valve_positions(const string &valve) const {
    vector<int> positions;
    for (int pos = 0; auto const &v: visits) {
        if (v.valve == valve) {
            positions.push_back(pos);
        }
        ++pos;
    }
    return positions;
}

vector<string> Route::get_valves() const{
    vector<string> valves;
    for (auto const &v: visits){
        valves.push_back(v.valve);
    }
    sort(valves.begin(), valves.end());
    valves.erase(unique(valves.begin(), valves.end()), valves.end());
    return valves;
}

std::ostream &operator<<(std::ostream &out, const Route &r) {
    out << "Rate: " << r.rate << " Valves: ";
    for (auto const &v: r.visits) {
        cout << v.valve << (v.open ? "_ " : " ");
    }
    return out;
}