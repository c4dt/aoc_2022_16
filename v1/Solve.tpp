//
// Created by Home on 01.01.23.
//

#include <algorithm>
#include <random>
#include "Solve.h"

using namespace std;

template<typename T>
void Solve<T>::init_best(size_t length) {
    while (best.size() < length) {
        best.push_back(random());
    }
    if (best.size() > length) {
        best.erase(best.begin() + int(length), best.end());
    }
}

template<typename T>
NumericVector Solve<T>::random() {
    return NumericVector(input.param_len(), input.param_values());
}

template<typename T>
unsigned Solve<T>::run_random(unsigned n) {
    init_best(1);
    unsigned best_fitness = get_best();
    for (; n > 0; --n) {
        auto new_vec = random();
        if (input.calc_fitness(new_vec) > best_fitness) {
            best.clear();
            best.push_back(new_vec);
            best_fitness = get_best();
        }
    }

    return get_best();
}

template<typename T>
unsigned Solve<T>::run_annealing(unsigned n, double p_keep_worse) {
    random_device r;
    default_random_engine e1(r());
    uniform_real_distribution<double> keep(0, 1);

    init_best(1);
    NumericVector &current = best.front();
    unsigned best_fitness = get_best();
    for (; n > 0; --n) {
        NumericVector new_vec = current.mutate();
        unsigned new_fitness = input.calc_fitness(new_vec);
        if (new_fitness > best_fitness || keep(e1) <= p_keep_worse) {
            best.clear();
            best.push_back(new_vec);
        }
    }
    return get_best();
}

template<typename T>
unsigned Solve<T>::run_genetic(unsigned n, size_t population, size_t random, double p_mutate) {
    random_device r;
    default_random_engine e1(r());
    uniform_int_distribution<size_t> choice(0, population + random - 1);
    uniform_real_distribution<double> mutate(0, 1);

    init_best(population + random);

    for (; n > 0; n--) {
        auto new_vec = best.at(choice(e1)).crossover(best.at(choice(e1)));
        if (mutate(e1) <= p_mutate) {
            new_vec.mutate();
        }
        best.push_back(new_vec);
    }

    for (auto &vec: best) {
        vec.set_fitness(input.calc_fitness(vec));
    }

    sort(best.begin(), best.end(), [](const NumericVector &a, const NumericVector &b) {
        return b.get_fitness() < a.get_fitness();
    });
    unique(best.begin(), best.end(), [](const NumericVector &a, const NumericVector &b) {
        return a.get_fitness() == b.get_fitness();
    });

    // Misuse init_best to throw away bad entries.
    init_best(population);

//    for (auto const &b: best){
//        cout << b.get_fitness() << endl;
//    }

    return get_best();
}

template<typename T>
unsigned Solve<T>::get_best() {
    return input.calc_fitness(best.front());
}
