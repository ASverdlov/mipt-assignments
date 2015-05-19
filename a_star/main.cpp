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
    Grid canonical({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 0});
    cout << canonical << "\n";

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
            vector<EMove> ans = solver.solve(grid, canonical, false, 1000);
            double elapsedTime = static_cast<double>(clock() - startTime) / CLOCKS_PER_SEC;

            cout << "\nTime: " << elapsedTime << "\nAnswer: " << ans << "\n";
        }
    }
    return 0;
}
