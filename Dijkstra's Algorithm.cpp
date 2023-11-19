#include <iostream>
#include <vector>
#include <limits>

const int INF = std::numeric_limits<int>::max();

void printSolution(const std::vector<int>& dist, int n, int src, int target, const std::vector<int>& parent) {
    std::cout << "Vertex\t Distance from Source\tPath";
    for (int i = 0; i < n; i++) {
        if (i != src && i == target) {
            std::cout << "\n" << i << " \t\t " << dist[i] << "\t\t" << src;
            int j = i;
            while (parent[j] != -1) {
                std::cout << " -> " << parent[j];
                j = parent[j];
            }
        }
    }
}

int minDistance(const std::vector<int>& dist, const std::vector<bool>& sptSet, int V) {
    int min = INF, min_index;

    for (int v = 0; v < V; v++)
        if (!sptSet[v] && dist[v] <= min)
            min = dist[v], min_index = v;

    return min_index;
}

void Dijkstra(const std::vector<std::vector<int>>& graph, int src, int V, int target) {
    std::vector<int> dist(V, INF);
    std::vector<bool> sptSet(V, false);
    std::vector<int> parent(V, -1);

    dist[src] = 0;

    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V);
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                parent[v] = u;
                dist[v] = dist[u] + graph[u][v];
            }
    }

    printSolution(dist, V, src, target, parent);
}

int main() {
    int V;
    std::cout << "Enter the number of vertices: ";
    std::cin >> V;

    std::vector<std::vector<int>> graph(V, std::vector<int>(V));
    std::cout << "Enter the adjacency matrix:\n";
    for (int i = 0; i < V; i++)
        for (int j = 0; j < V; j++)
            std::cin >> graph[i][j];

    int source, target;
    std::cout << "Enter the source node: ";
    std::cin >> source;
    std::cout << "Enter the target node: ";
    std::cin >> target;

    Dijkstra(graph, source, V, target);

    return 0;
}
