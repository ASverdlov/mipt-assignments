#include <iostream>
#include <cstdlib>

#include "distance_estimators.h"
#include "a_star.h"
#include "grid.h"

using std::cin;
using std::cout;
using std::vector;

static DEFunctionHolder distEstimators[1] = {
    {manhattanLCDistanceEstimator, "Manhattan + L or C"}
};

int main()
{
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    Solver solver;

    int T; cin >> T;
    for (int test = 1; test <= T; ++test) {
        Grid grid;
        cin >> grid;
        cout << grid;
        
        cout << "Test: " << test << ":\n";
        if (!isSolvable(grid)) {
            cout << "This puzzle is not solvable.\n";
            continue;
        }

        for (const auto& estimatorHolder : distEstimators) {
            clock_t startTime = clock();

            solver.setEstimator(estimatorHolder.function);

            vector<EMove> ans = solver.solve(grid, false);

            double elapsedTime = static_cast<double>(clock() - startTime) / CLOCKS_PER_SEC;
            cout << "\tWith estimator: " << estimatorHolder.name << ", time: " << elapsedTime
                      << ", answer: " << ans << '\n';
        }
    }
    return 0;
}
