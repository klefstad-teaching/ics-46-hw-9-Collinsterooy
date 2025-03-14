#include "dijkstras.h"


vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous)
{
	int numVertices = G.size();
	vector<int> distances(numVertices, INF);
	vector<bool> visited(numVertices, false);
	distances[source] = 0;
	previous[source] = UNDEFINED;
	priority_queue<pair<int, int>> minHeap; // assume minHeap comparator
	minHeap.push({ source, 0 });
	while (!minHeap.empty()) {
		int u = minHeap.top().first;
		minHeap.pop();
		if (visited[u]) continue;
		visited[u] = true;
		for (const Edge& edge : G[u]) {
			int v = edge.dst;
			int weight = edge.weight;
			if (!visited[v] && distances[u] + weight < distances[v]) {
				distances[v] = distances[u] + weight;
				previous[v] = u;
				minHeap.push({ v, distances[v] });
			}
		}
	}
	return distances;


}
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination)
{
	vector<int> currPath;
	if (distances[destination] == INF) {
		
		return currPath;
	}

	
	for (int at = destination; at != UNDEFINED; at = previous[at]) {
		currPath.push_back(at);
	}

	
	reverse(currPath.begin(), currPath.end());

	return currPath;
}
void print_path(const vector<int>& v, int total)
{
	for (int destination = 0; destination < total; ++destination) {
		if (v[destination] == UNDEFINED) {
			cout << "No path to " << destination << endl;
			continue;
		}

		vector<int> currPath;
		for (int curr = destination; curr != UNDEFINED; curr = v[curr]) {
			currPath.push_back(curr);
		}
		reverse(currPath.begin(), currPath.end());

		cout << "Path to " << destination << ": ";
		for (size_t i = 0; i < currPath.size(); ++i) {
			if (i > 0) cout << " -> ";
			cout << currPath[i];
		}
		cout << endl;
	}
}