#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <iostream>

#include <unordered_set>
#include <vector>
using namespace std;


///// CONSTANTS AND STRUCTS /////

const int MAXN = 100;
const int MAXM = 10000;

/* Only edge indices are stored. */;
typedef unordered_set<int> EdgeSet;

struct Edge {
    int a, b;
};


/////////// GLOBALS //////////////

/* Input */
int n, m;
vector<int> g[MAXN]; /* g[v][i] -- index of i'th edge */
Edge edges[MAXM];

/* Solution */
EdgeSet A; 
int cur_k, cur_m, cur_s;


//////////// HELPERS //////////////

bool is_2matching(const EdgeSet& C) {
    for (int v = 0; v < n; ++v) {
        int num_incident = 0;
        for (int e : g[v]) {
            if (A.count(e) != C.count(e))
                ++num_incident;
        }
        if (num_incident > 2) return false;
    }
    return true;
}

vector<int> components[MAXN];
int col[MAXN];
int deg[MAXN];
int color;
void dfs(int v, int p, const EdgeSet& C) {
    if (col[v]) return;
    col[v] = color;
    components[color - 1].push_back(v);
    if (p != -1) {
        ++deg[v];
        ++deg[p];
    }

    for (int e : g[v]) if (v != p) {
        if (A.count(e) != C.count(e)) {
            int u = edges[e].a == v ? edges[e].b : edges[e].a;
            assert(u != v);
            dfs(u, v, C);
        }
    }
}

void find_k_m_s(const EdgeSet& C, int& k, int& m, int& s) {
    /* Initialize working data */
    for (int v = 0; v < n; ++v) {
        col[v] = 0;
        deg[v] = 0;
        components[v].clear();
    }
    color = 0;

    /* Find components and vertices' degrees */
    for (int v = 0; v < n; ++v) {
        if (col[v] == 0) {
            ++color;
            dfs(v, -1, C);
        }
    }

    /* Deduce k, m, s numbers from degrees and components */
    k = color;
    s = 0;
    m = 0;
    for (int c = 0; c < color; ++c) {
        if (components[c].size() == 1)
            ++s;
        bool is_cycle = true;
        for (int v : components[c]) {
            if (deg[v] != 2) {
                is_cycle = false;
                break;
            }
        }
        if (is_cycle) {
            m += components[c].size();
        }
    }
}


///////////// SOLUTION //////////////

bool find_improve(int from, int cnt, EdgeSet& C,
                  int& new_k, int& new_m, int& new_s) {
    if (cnt == 0) {
        if (!is_2matching(C)) return false;
        find_k_m_s(C, new_k, new_m, new_s);

#if 1
        cout << "Test improvement, edge set:\n";
        for (int e = 0; e < m; ++e) {
            if (A.count(e) != C.count(e)) {
                cout << "Edge: " << edges[e].a + 1 << " "
                                 << edges[e].b + 1 << endl;
            }
        }
        cout << "K: " << new_k << endl;
        cout << "M: " << new_m << endl;
        cout << "S: " << new_s << endl;
        cout << endl;
#endif

        if (new_k < cur_k) {
            return true;
        } else if (new_k == cur_k && new_m > cur_m) {
            return true;
        } else if (new_k == cur_k && new_m == cur_m && new_s < cur_s) {
            return true;
        }
        return false;
    }

    for (int i = from; i < m; ++i) {
        C.insert(i);
        if (find_improve(i + 1, cnt - 1, C, new_k, new_m, new_s)) {
            return true;
        }
        C.erase(i);
    }
    return false;
}

void solve_tsp() {
    cur_k = n;
    cur_m = 0;
    cur_s = n;

    EdgeSet C;
    while (true) {
        int new_k, new_m, new_s;
        bool found = false;

        /* Iterate over C size */
        for (int K = 1; K <= 15; ++K) {
            C.clear();
            if (find_improve(0, K, C, new_k, new_m, new_s)) {
                found = true;
                break;
            }
        }
        if (!found) break;

        /* Apply change */
        cur_k = new_k;
        cur_m = new_m;
        cur_s = new_s;
        for (auto edge : C) {
            if (A.count(edge) == 0) {
                A.insert(edge);
            } else {
                A.erase(edge);
            }
        }
    }
}

int main() {
    /* Take input.txt as input */
    freopen("input.txt", "r", stdin);

    /* Read the graph.
     * Only 1-edges are passed here (others are assumed to be 2-edges)
     */
    cin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        --a, --b;

        edges[i] = {a, b};
        g[a].push_back(i);
        g[b].push_back(i);
    }

    solve_tsp();

    cout << "Solution\n";
    cout << "K: " << cur_k << endl;
    cout << "M: " << cur_m << endl;
    cout << "S: " << cur_s << endl;
    for (int e : A) {
        cout << "Edge: " << edges[e].a + 1 << ' ' << edges[e].b + 1 << endl;
    }

    return 0;
}
