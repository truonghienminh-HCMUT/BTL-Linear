#include <iostream>
#include <vector>
#include <iomanip>
#include <set>
#include <algorithm>

using namespace std;

#define TEST_CASE 
#define pb push_back
#define int long long
#define FOR(i, a, b) for(auto i = a; i < b; i++)
#define io(a) if (a) freopen("input_alt.txt", "r", stdin), freopen("output_alt.txt", "w", stdout)

const int maxn = 1e5 + 1, INF = 1e18;
int n, m, mode;
vector<pair<int, int>> adj[maxn];

/*
    n: number of vertices
    m: number of edges
    mode: 0 for undirected graph, 1 for directed graph
    adj: adjacency list
    dist: distance matrix
    next: next matrix
    t: number of queries
    u, v: query vertices
    neg_cycle: boolean array to check if a vertex is affected by a negative cycle
*/

void inp(){
    cin >> n >> m >> mode;
    FOR(i, 0, m){
        int x, y, w;
        cin >> x >> y >> w;
        adj[x].pb({y, w});
        if (mode == 0)
            adj[y].pb({x, w});
    }
}

void floyd_warshall(int n, vector<vector<int>> &dist, vector<vector<int>> &next, vector<vector<set<vector<int>>>> &all_paths) {
    FOR(i, 1, n + 1) {
        FOR(j, 1, n + 1) {
            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INF;
            next[i][j] = 0;
            all_paths[i][j].clear();
        }
    }

    FOR(u, 1, n + 1) {
        for (auto &edge : adj[u]) {
            int v = edge.first, w = edge.second;
            if (w < dist[u][v]) {
                dist[u][v] = w;
                next[u][v] = v;
                all_paths[u][v].clear();
                all_paths[u][v].insert({u, v});
            } else if (w == dist[u][v]) {
                all_paths[u][v].insert({u, v});
            }
        }
    }

    FOR(k, 1, n + 1) {
        FOR(i, 1, n + 1) {
            FOR(j, 1, n + 1) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] <= dist[i][j]) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        next[i][j] = next[i][k];
                        all_paths[i][j].clear();
                        for (const auto &path1 : all_paths[i][k]) {
                            for (const auto &path2 : all_paths[k][j]) {
                                vector<int> new_path = path1;
                                new_path.insert(new_path.end(), path2.begin() + 1, path2.end());
                                all_paths[i][j].insert(new_path);
                            }
                        }
                    } else if (dist[i][k] + dist[k][j] == dist[i][j]) {
                        for (const auto &path1 : all_paths[i][k]) {
                            for (const auto &path2 : all_paths[k][j]) {
                                vector<int> new_path = path1;
                                new_path.insert(new_path.end(), path2.begin() + 1, path2.end());
                                all_paths[i][j].insert(new_path);
                            }
                        }
                    }
                }
            }
        }
    }
}

vector<int> reconstruct_path(int u, int v, const vector<vector<int>>& next){
    vector<int> path;
    if (next[u][v] == 0){
        if (u == v) path.push_back(u);
        return path;
    }
    path.push_back(u);
    while (u != v){
        u = next[u][v];
        path.push_back(u);
    }
    return path;
}

void print_all_paths(int u, int v, const vector<vector<set<vector<int>>>> &all_paths) {
    if (all_paths[u][v].empty()) {
        return;
    }
    for (const auto &path : all_paths[u][v]) {
        for (int node : path) {
            cout << node << " ";
        }
        cout << endl;
    }
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    io(true);
    inp();

    vector<vector<int>> dist(n + 1, vector<int>(n + 1));
    vector<vector<int>> next(n + 1, vector<int>(n + 1));
    vector<vector<set<vector<int>>>> all_paths(n + 1, vector<set<vector<int>>>(n + 1));

    floyd_warshall(n, dist, next, all_paths);

    vector<bool> neg_cycle(n + 1, false);
    FOR(i, 1, n + 1) {
        if (dist[i][i] < 0) {
            neg_cycle[i] = true;
        }
    }

    int t, u, v;
    // cout << "Floyd-Warshall Algorithm for " << (mode == 0 ? "undirected" : "directed") << " graph.\n";
    // cout << "Matrix of shortest distances:\n";
    // cout << setw(5) << "i\\j";
    // FOR(i, 1, n + 1)
    //     cout << setw(5) << i;
    
    FOR(i, 1, n + 1){
        // cout << endl << setw(5) << i;
        FOR(j, 1, n + 1){
            if (dist[i][j] == INF)
                cout << setw(5) <<  "INF";
            else {
                bool flag = false;
                FOR(k, 1, n + 1) {
                    if (neg_cycle[k] && dist[i][k] != INF && dist[k][j] != INF) {
                        flag = true;
                        break;
                    }
                }
                if (flag)
                    cout << setw(5) << "-INF";
                else
                    cout << setw(5) << dist[i][j];
            }
        }
        cout << endl;
    }
    cout << '\n';
    #ifdef TEST_CASE
    t = 1;
    while (t--) {
        cin >> u >> v;
        bool neg = false;
        FOR(k, 1, n + 1) {
            if (neg_cycle[k] && dist[u][k] != INF && dist[k][v] != INF) {
                neg = true;
                break;
            }
        }
        if (neg)
            cout << "-INF\n";
        else if (dist[u][v] == INF)
            cout << "INF\n";
        else {
            if (u == v) {
                cout << u << endl;
                continue;
            }
            if (all_paths[u][v].size() > 1)
                print_all_paths(u, v, all_paths);
            else {
                vector<int> path = reconstruct_path(u, v, next);
                for (int node : path) {
                    cout << node << " ";
                }
                cout << endl;
            }
        }
    }
    #endif

    return 0;
}