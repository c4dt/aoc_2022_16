//
// Created by Home on 01.01.23.
//

#include "NumericVector.h"
#include <random>
#include <iostream>

using namespace std;

void NumericVector::randomize() {
    random_device r;
    default_random_engine e1(r());
    uniform_int_distribution<unsigned> value(0, value_max - 1);

    while (values.size() < length) {
        values.push_back(value(e1));
    }
}

NumericVector NumericVector::mutate() {
    random_device r;
    default_random_engine e1(r());
    uniform_int_distribution<unsigned> pos(0, length - 1);
    uniform_int_distribution<unsigned> value(0, value_max - 1);

    NumericVector new_vec(length, value_max, values);
    new_vec.values.at(pos(e1)) = value(e1);
    return new_vec;
}

NumericVector NumericVector::crossover(const NumericVector &other) {
    random_device r;
    default_random_engine e1(r());
    uniform_int_distribution<int> pos(1, int(length) - 1);
    int pos_cut = pos(e1);

    NumericVector new_vec(length, value_max, values);
    new_vec.values.erase(new_vec.values.begin() + pos_cut, new_vec.values.end());
    new_vec.values.insert(new_vec.values.begin() + pos_cut, other.values.begin() + pos_cut, other.values.end());

    return new_vec;
}

unsigned NumericVector::get_fitness() const {
    assert(fitness != -1);
    return fitness;
}

void NumericVector::set_fitness(unsigned fit) {
    fitness = fit;
}

vector<unsigned> NumericVector::get_values() {
    return values;
}

void testNumeric() {
    NumericVector v1(10, 2);
    assert(v1.values.size() == 10);
    for (const auto val: v1.values) {
        assert(val < 2);
    }

    v1 = NumericVector(10, 100);
    NumericVector v2(10, 100);
    assert(any_of(v1.values.begin(), v1.values.end(), [&v2](unsigned v) {
        static int i;
        return v != v2.values.at(i++);
    }));

    NumericVector v3 = v1.mutate();
    assert(count_if(v1.values.begin(), v1.values.end(), [&v3](unsigned v) {
        static int i;
        return v != v3.values.at(i++);
    }) == 1);

    v3 = v1.crossover(v2);
    unsigned v1_cnt = 0, v2_cnt = 0;
    for_each(v3.values.begin(), v3.values.end(), [&v1_cnt, &v2_cnt, &v1, &v2](unsigned v) {
        static int i;
        if (v == v1.values.at(i)) { v1_cnt++; }
        if (v == v2.values.at(i++)) { v2_cnt++; }
    });
    assert(v1_cnt + v2_cnt >= 10);
}