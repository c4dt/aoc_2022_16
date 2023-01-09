#include <iostream>
#include <cmath>
#include "NumericVector.h"
#include "Tunnels.h"
#include "OnePerson.h"
#include "TwoPersons.h"
#include "Solve.h"

using namespace std;

int main() {
    testNumeric();
    test_tunnels();
    test_oneperson();

    Tunnels t("../input.txt");
    cout << t << endl;
    OnePerson input(t);
//    TwoPersons input(t);
    Solve solver_rnd(input);
    Solve solver_annealing(input);
    vector<Solve<OnePerson>> solvers_genetic;
    for (int i = 0; i < 100; i++) {
        solvers_genetic.emplace_back(input);
    }
    unsigned rounds = 100;
    for (int i = 0; i < rounds; i++) {
        double mutate = pow(1 - i / (rounds - 1.), 10.);
        cout << "Round " << i;
        cout << " - random: " << solver_rnd.run_random(1000);
        cout << " - annealing: " << solver_annealing.run_annealing(1000, mutate);
        cout << " - genetics: ";
        unsigned random = 0;
        vector<unsigned> fitnesses;
        for (auto &solver: solvers_genetic) {
            auto latest = solver.run_genetic(1000, 10 * (random + 1), random, mutate);
            cout << latest << " ";
            fitnesses.push_back(latest);
            ++random;
        }
        sort(fitnesses.begin(), fitnesses.end());
        cout << endl << "Best is: " << fitnesses.back();
        cout << endl;
    }
    return 0;
}
