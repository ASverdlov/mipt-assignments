#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <cmath>

#include <chrono>
#include <limits>

#include <vector>

using std::vector;
using std::swap;
using std::normal_distribution;
using std::default_random_engine;
using std::cout;
using std::cerr;
using std::cin;

/************************ Disjoint-Set-Union *************************/


class DSU
{
public:
    void initSets(size_t n);
    int  findSet(size_t v);
    bool uniteSets(size_t u, size_t v);

private:
    vector<int> parent;
    vector<int> size;
};

void DSU::initSets(size_t n)
{
    parent.assign(n, 0);
    for (size_t idx = 0; idx < n; ++idx) {
        parent[idx] = idx;
    }
    size.assign(n, 1);
}

int DSU::findSet(size_t v)
{
    if (v == parent[v]) {
        return v;
    }
    return parent[v] = findSet(parent[v]);
}

bool DSU::uniteSets(size_t v1, size_t v2)
{
    v1 = findSet(v1);
    v2 = findSet(v2);
    if (v1 == v2) {
        return false;
    }
    if (size[v1] < size[v2]) {
        swap(v1, v2);
    }
    parent[v2] = v1;
    size[v1] += size[v1];
    return true;
}

/***************************** Solver *******************************/

struct Point
{
    double x, y;
};

struct Edge
{
    int from, to;
    double length;
};

bool operator<(const Edge& lhs, const Edge& rhs) 
{
    return lhs.length < rhs.length;
}

class Solver
{
public:
    vector<Point> solve(const vector<Point>& points);

private:
    static double getDistance(Point point1, Point point2);
    void getMST();
    void traverseTree(int v, int p);

    vector<Point> cycle;

    // minimum spanning tree
    vector<vector<Edge>> mst;

    // points given in input
    vector<Point> points;
};


double Solver::getDistance(Point point1, Point point2) 
{
    return sqrt((point1.x - point2.x) * (point1.x - point2.x) + 
                (point1.y - point2.y) * (point1.y - point2.y));
}

void Solver::traverseTree(int v, int p)
{
    for (auto& edge : mst[v]) if (edge.to != p) {
        traverseTree(edge.to, v);
    }
    cycle.push_back(points[v]);
}

vector<Point> Solver::solve(const vector<Point>& points)
{
    this->points = points;
    getMST();

    cycle.clear();
    traverseTree(0, 0);

    return cycle;
}

void Solver::getMST()
{
    DSU dsu;
    dsu.initSets(points.size());

    vector<Edge> edges;
    for (int idx1 = 0; idx1 < points.size(); ++idx1) {
        for (int idx2 = idx1 + 1; idx2 < points.size(); ++idx2) {
            Edge currentEdge = {idx1, idx2, getDistance(points[idx1], points[idx2])};
            edges.push_back(currentEdge);
        }
    }
    sort(edges.begin(), edges.end());

    int nEdges = 0;

    mst.assign(points.size(), vector<Edge>());
    for (const auto& edge : edges) {
        bool hasUnited = dsu.uniteSets(edge.from, edge.to);
        if (hasUnited) {
            ++nEdges;
            mst[edge.from].push_back({edge.from, edge.to, edge.length});
            mst[edge.to].push_back({edge.to, edge.from, edge.length});
        }
    }

    cout << "nEdges: " << nEdges << "\n";
}

/*************************** Main logic *****************************/


// generates n random points near center point
vector<Point> generateRandomPoints(Point center, size_t n, double sigma, default_random_engine& generator)
{
    normal_distribution<double> distribution(0.0, sigma);

    vector<Point> points(n);
    for (int idx = 0; idx < n; ++idx) {
        points[idx].x = center.x + distribution(generator);
        points[idx].y = center.y + distribution(generator);
    }
    return points;
}

vector<Point> generateInput(size_t centers, size_t aroundCenters, double sigma1, 
                       double sigma2, default_random_engine& generator)
{
    normal_distribution<double> distribution(0.0, sigma1);

    vector<Point> points;
    for (int idx = 0; idx < centers; ++idx) {
        // generate center
        Point point;
        point.x = distribution(generator);
        point.y = distribution(generator);
        points.push_back( point );

        // generate points around center
        vector<Point> pointsNearby = generateRandomPoints(point, aroundCenters, sigma2, generator);
        points.insert(points.end(), pointsNearby.begin(), pointsNearby.end());
    }
    return points;
}

int main()
{
    freopen("output.txt", "w", stdout);

    // set up random device
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    default_random_engine generator(seed);

    // get input
    int centers, aroundCenters;
    double sigma1, sigma2;

    centers = 10;
    aroundCenters = 10;
    sigma1 = 10.0;
    sigma2 = 2.0;
    //cin >> centers >> aroundCenters >> sigma1 >> sigma2;

    // init Solver
    Solver solver;

    int nTests = 2;
    for (int test = 1; test <= nTests; ++test) {
        vector<Point> points = generateInput(centers, aroundCenters, sigma1, sigma2, generator);

        cout << "Generated points:\n";
        for (auto point : points) {
            cout << "(" << point.x << ", " << point.y << ")\n";
        }

        vector<Point> cycle = solver.solve(points);

        cout << "Calculated answer:\n";
        for (auto point : cycle) {
            cout << "(" << point.x << ", " << point.y << ")\n";
        }
    }

    return 0;
}
