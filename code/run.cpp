#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

#define TEST_CASE 
#define pb push_back
#define int long long
#define FOR(i, a, b) for(auto i = a; i < b; i++)
#define io(a) if (a) freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout)

const int maxn = 1e5 + 1, INF = 1e18;
int n, m, mode;
vector<pair<int, int>> adj[maxn];
// int pre_unused[maxn];
// bool visited_unused[maxn];

// VARIABLE NAME EXPLANATION
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

void floyd_warshall(int n, vector<vector<int>>& dist, vector<vector<int>>& next){
    FOR(i, 1, n + 1){
        FOR(j, 1, n + 1){
            if (i == j)
                dist[i][j] = 0;
            else
                dist[i][j] = INF;
            next[i][j] = 0;
        }
    }

    FOR(u, 1, n + 1){
        for (auto& edge : adj[u]){
            int v = edge.first, w = edge.second;
            dist[u][v] = min(dist[u][v], w);
            next[u][v] = v;
        }
    }

    FOR(k, 1, n + 1){
        FOR(i, 1, n + 1){
            FOR(j, 1, n + 1){
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]){
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
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

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    io(true);
    inp();

    vector<vector<int>> dist(n + 1, vector<int>(n + 1));
    vector<vector<int>> next(n + 1, vector<int>(n + 1));

    floyd_warshall(n, dist, next);

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
    // cin >> t;
    t = 1;
    while (t--){
        cin >> u >> v;
        bool neg = false;
        FOR(k, 1, n + 1) {
            if (neg_cycle[k] && dist[u][k] != INF && dist[k][v] != INF) {
                neg = true;
                break;
            }
        }
        if (neg)
            // cout << "- Path from " << u << " to " << v << " is affected by a negative cycle.\n";
            cout << "-INF\n";
        else if (dist[u][v] == INF)
            // cout << "- No path from " << u << " to " << v << ".\n";
            cout << "INF\n";
        else{
            if (u == v){
                cout << u << endl;
                continue;
            }
            vector<int> path = reconstruct_path(u, v, next);
            FOR(i, 0, path.size()){
                cout << path[i] << " ";
            }
            cout << endl;
        }
    }
    #endif

    return 0;
}