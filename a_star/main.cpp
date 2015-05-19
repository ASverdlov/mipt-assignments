#include <iostream>
#include <cstdlib>

#include "distance_estimators.h"
#include "a_star.h"
#include "grid.h"

using std::cin;
using std::cout;
using std::vector;

static DEFunctionHolder distEstimators[] = {
    {manhattanLAndCDistanceEstimator, "Manhattan + L & C"},
    {manhattanLOrCDistanceEstimator, "Manhattan + L | C"},
    //{manhattanDistanceEstimator, "Manhattan"}
};

int main()
{
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    Solver solver;

    int T; cin >> T;
    for (int test = 1; test <= T; ++test) {
        cout << "\n\n--------------- Test: " << test << " -------------------------------\n";

        Grid grid;
        cin >> grid;
        cout << grid;
        
        if (!isSolvable(grid)) {
            cout << "\nThis puzzle is not solvable.";
            continue;
        } else {
            cout << "\nThis puzzle is solvable.";
        }

        for (const auto& estimatorHolder : distEstimators) {
            solver.setEstimator(estimatorHolder.function);

            cout << "\nEstimator started: " << estimatorHolder.name;

            clock_t startTime = clock();
            vector<EMove> ans = solver.solve(grid, false, 1000);
            double elapsedTime = static_cast<double>(clock() - startTime) / CLOCKS_PER_SEC;

            cout << "\nTime: " << elapsedTime << "\nAnswer: " << ans << "\n";
        }
    }
    return 0;
}
