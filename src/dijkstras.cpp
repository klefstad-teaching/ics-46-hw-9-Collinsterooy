#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int numVertices = G.size();
    vector<int> distances(numVertices, INF);
    vector<bool> visited(numVertices, false);

    distances[source] = 0;
    previous.assign(numVertices, UNDEFINED);

    // Min-heap to store (distance, node)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;
    minHeap.push({0, source});

    while (!minHeap.empty()) {
        int u = minHeap.top().second;
        int dist = minHeap.top().first;
        minHeap.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            // Relaxation step
            if (!visited[v] && distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v], v});
            }
        }
    }

    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    
    if (destination < 0 || destination >= distances.size() || distances[destination] == INF) {
        return path; // No valid path
    }

    for (int at = destination; at != UNDEFINED; at = previous[at]) {
        path.insert(path.begin(), at);
    }

    return path;
}

void print_path(const vector<int>& v,  int total) {
    for (int destination = 0; destination < total; ++destination) {
        // Fix: Check for invalid path
        if (v[destination] == UNDEFINED) {
            cout << "No path to " << destination << endl;
            continue;
        }

        vector<int> currPath;
        for (int curr = destination; curr != UNDEFINED; curr = v[curr]) {
            currPath.insert(currPath.begin(), curr);
        }

        cout << "Path to " << destination << ": ";
        for (size_t i = 0; i < currPath.size(); ++i) {
            if (i > 0) cout << " -> ";
            cout << currPath[i];
        }
        cout << " (Cost: " << (currPath.size() > 1 ? currPath.back() : 0) << ")" << endl;
    }
}
