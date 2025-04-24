#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// BFS function to find if there is a path from source to sink
bool bfs(vector<vector<int>>& rGraph, int s, int t, vector<int>& parent) {
    int V = rGraph.size();
    vector<bool> visited(V, false);
    queue<int> q;

    q.push(s);
    visited[s] = true;
    parent[s] = -1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v = 0; v < V; ++v) {
            if (!visited[v] && rGraph[u][v] > 0) {
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    return visited[t];
}

int fordFulkerson(vector<vector<int>>& graph, int s, int t) {
    int V = graph.size();
    vector<vector<int>> rGraph = graph; // Residual graph
    vector<int> parent(V);
    int maxFlow = 0;

    while (bfs(rGraph, s, t, parent)) {
        int path_flow = INT_MAX;

        // Find minimum residual capacity of the augmenting path
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);
        }

        // Update residual capacities
        for (int v = t; v != s; v = parent[v]) {
            int u = parent[v];
            rGraph[u][v] -= path_flow;
            rGraph[v][u] += path_flow;
        }

        maxFlow += path_flow;
    }

    return maxFlow;
}

int main() {
    int V, E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    vector<vector<int>> graph(V, vector<int>(V, 0));

    cout << "Enter edges (format: from to capacity):\n";
    for (int i = 0; i < E; ++i) {
        int u, v, cap;
        cin >> u >> v >> cap;
        u--; // Adjust for 0-based indexing
        v--; // Adjust for 0-based indexing
        if (u >= 0 && u < V && v >= 0 && v < V) {
            graph[u][v] = cap; // directed graph
        } else {
            cout << "Invalid edge, vertices out of range.\n";
        }
    }

    int s, t;
    cout << "Enter source and sink: ";
    cin >> s >> t;
    s--; // Adjust for 0-based indexing
    t--; // Adjust for 0-based indexing

    if (s < 0 || s >= V || t < 0 || t >= V) {
        cout << "Invalid source or sink.\n";
        return -1;
    }

    int maxFlow = fordFulkerson(graph, s, t);
    cout << "Maximum Flow: " << maxFlow << endl;

    return 0;
}

