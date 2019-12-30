//
// Created by ilya on 20/12/2019.
//

#include "Graph.h"

Graph::Graph(int V) : G(V) {}

void Graph::add_edge(int v, int w, double weight) {
    G[v].push_back(std::make_pair(w, weight));
}

void Graph::add_undirected_edge(int v, int w, double weight) {
    add_edge(v, w, weight);
    add_edge(w, v, weight);
}

size_t Graph::size() const {
    return G.size();
}

const std::vector<std::pair<int, double>> &Graph::get_siblings(int u) const {
    return G[u];
}

double Graph::get_weight(int u, int v) const {
    // return weight of an edge between two vertices
    // or -1 if no such edge exists
    for (auto &elem : G[u]) {
        if (elem.first == v) {
            return elem.second;
        }
    }

    return -1;
}
