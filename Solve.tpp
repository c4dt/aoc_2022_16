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
        best.push_back(input.get_random());
    }
    if (best.size() > length) {
        best.erase(best.begin() + int(length), best.end());
    }
}

template<typename T>
unsigned Solve<T>::run_random(unsigned n) {
    init_best(1);
    unsigned best_fitness = best.front().rate;
    for (; n > 0; --n) {
        Route new_route = input.get_random();
        if (new_route.rate > best_fitness) {
            best.clear();
            best.push_back(new_route);
            best_fitness = new_route.rate;
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
    Route &current = best.front();
    unsigned best_fitness = get_best();
    for (; n > 0; --n) {
        Route new_vec = input.get_mutation(current);
        if (new_vec.rate > best_fitness || keep(e1) <= p_keep_worse) {
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
        auto new_vec = input.get_crossover(best.at(choice(e1)), best.at(choice(e1)));
        if (mutate(e1) <= p_mutate) {
            best.push_back(input.get_mutation(new_vec));
        }
        best.push_back(new_vec);
    }

    // This also sorts the 'best' vector.
    unsigned best_fitness = get_best();

    // Misuse init_best to throw away bad entries.
    init_best(population);

//    cout << "Best after genetic: " << best.front() << endl;

//    for (auto const &b: best){
//        cout << b.get_fitness() << endl;
//    }

    return best_fitness;
}

template<typename T>
unsigned Solve<T>::get_best() {
    sort(best.begin(), best.end(), [](const Route &a, const Route &b) {
        return b.rate < a.rate;
    });
    unique(best.begin(), best.end(), [](const Route &a, const Route &b) {
        return a.rate == b.rate;
    });

//    for (auto const &b: best) {
//        cout << b << endl;
//    }
//
    return best.front().rate;
}
