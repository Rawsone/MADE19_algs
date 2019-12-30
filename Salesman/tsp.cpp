//
// Created by ilya on 20/12/2019.
//
#include <set>
#include <numeric>
#include "tsp.h"


Graph PrimsMST(const Graph &g) {
    Graph new_graph(g.size());
    // set used as priority queue
    // first value is the weight
    // second is the number of the vertex
    std::set<std::pair<double, int>> vertices;

    // distances with big initial values
    // storing INT32_MAX works 2 times slower
    // and gets TL idk why
    std::vector<double> dist(g.size(), 100000);

    // To store parent array which in turn store MST
    std::vector<int> parents(g.size(), -1);

    // To keep track of vertices included in MST
    std::vector<bool> added(g.size(), false);

    // Taking vertex 0 as the first
    int src = 0;
    vertices.emplace(std::make_pair(0, src));
    dist[src] = 0;

    while (!vertices.empty()) {

        // pop the vertex with the smallest distance
        int u = vertices.begin()->second;
        vertices.erase(vertices.begin());

        added[u] = true;
        if (u != src)
            new_graph.add_undirected_edge(parents[u], u, dist[u]);

        // Traverse all adjacent vertices of u
        for (auto x : g.get_siblings(u)) {

            int v = x.first;
            double weight = x.second;

            // if found the better
            if (!added[v] && dist[v] > weight) {
                // Update the distance to v
                // Delete old
                auto old = vertices.find({dist[v], v});
                if (old != vertices.end())
                    vertices.erase(old);
                dist[v] = weight;
                // Add new
                vertices.emplace(std::make_pair(dist[v], v));
                // Update parent
                parents[v] = u;
            }
        }
    }
    return new_graph;
}

double Exact(const Graph &g) {
    std::vector<int> indices(g.size());
    std::iota(std::begin(indices), std::end(indices), 0);
    double min_cost = 100000;
    do {
        double current_cost = 0;
        for (int i = 1; i < indices.size(); i++)
            current_cost += g.get_weight(indices[i - 1], indices[i]);
        // return back to initial state
        current_cost += g.get_weight(indices.size() - 1, 0);
        min_cost = std::min(min_cost, current_cost);
    } while (std::next_permutation(indices.begin() + 1, indices.end()));

    return min_cost;
}

double dfs(const Graph &g, std::vector<bool> &discovered, double current_weight, int u) {
    // visit all vertices using
    // recursive dfs
    discovered[u] = true;
    for (auto v : g.get_siblings(u)) {
        if (!discovered[v.first]) {
            current_weight += v.second;
            current_weight = dfs(g, discovered, current_weight, v.first);
            current_weight += v.second;
        }
    }
    return current_weight;
}

double walk_weight(const Graph &g) {
    std::vector<bool> discovered(g.size(), false);
    double weight = 0;
    int src = 0;
    return dfs(g, discovered, weight, src);
}

double PrimsApproximate(const Graph &g) {
    const Graph &mst = PrimsMST(g);
    return walk_weight(mst);
}
