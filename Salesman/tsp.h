//
// Created by ilya on 20/12/2019.
//
#pragma once

#include "point.h"
#include "Graph.h"

#include <vector>

Graph PrimsMST(const Graph &g);

double PrimsApproximate(const Graph &g);

double Exact(const Graph &g);

double dfs(const Graph &g, std::vector<bool> &discovered, double current_weight, int u);

double walk_weight(const Graph &g);
