//
// Created by ilya on 20/12/2019.
//
#pragma once

#include <vector>

class Graph {
public:
    void add_edge(int v, int w, double weight);

    void add_undirected_edge(int v, int w, double weight);

    explicit Graph(int V);

    size_t size() const;

    const std::vector<std::pair<int, double>> &get_siblings(int u) const;

    double get_weight(int u, int v) const;

private:
    std::vector<std::vector<std::pair<int, double>>> G;

};


