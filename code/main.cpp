/*
    THIS IS JUST A TEST, NOT OFFICIAL CODE
*/

#include <iostream>
#include <vector>
#include <limits>

using namespace std;

#define INF numeric_limits<int>::max()
#define FOR(i, a, b) for(auto i = a; i < b; i++)
#define io(a) if (a) freopen("input.txt", "r", stdin), freopen("output.txt", "w", stdout)

void floydWarshall(const vector<int> graph[], vector<vector<int>>& dist, vector<vector<int>>& next){
    int V = dist.size();
    dist.resize(V, vector<int>(V, INF));
    next.resize(V, vector<int>(V, -1));

    FOR(i, 0, V){
        FOR(j, 0, V){
            dist[i][j] = graph[i][j];
            if(graph[i][j] != INF){
                next[i][j] = j;
            }
        }
    }

    FOR(k, 0, V){
        FOR(i, 0, V){
            FOR(j, 0, V){
                if(dist[i][k] != INF && dist[k][j] != INF){
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                    if(dist[i][j] == dist[i][k] + dist[k][j]){
                        next[i][j] = next[i][k];
                    }
                }
            }
        }
    }
}

vector<int> constructPath(int u, int v, const vector<vector<int>>& next){
    if(next[u][v] == -1) return {};
    vector<int> path = {u};
    while(u != v){
        u = next[u][v];
        path.push_back(u);
    }
    return path;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    io(true);

    int V, E;
    cin >> V >> E;

    vector<int> graph[V];
    FOR(i, 0, V){
        graph[i].resize(V);
        graph[i][i] = 0;
    }

    vector<int> edges[E];
    FOR(i, 0, E){
        int u, v, w;
        cin >> u >> v >> w;
        graph[u][v] = w;
        edges[i] = {u, v, w};
    }

    vector<vector<int>> dist(V), next;
    floydWarshall(graph, dist, next);

    int u, v;
    cin >> u >> v;
    vector<int> path = constructPath(u, v, next);

    if(path.empty()){
        cout << "No path exists between " << u << " and " << v << '\n';
    } else {
        cout << "Shortest path between " << u << " and " << v << ": ";
        for(int i : path){
            cout << i << " ";
        }
        cout << "\nDistance: " << dist[u][v] << '\n';
    }

    return 0;
}
