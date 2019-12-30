#include "point.h"
#include "Graph.h"
#include "tsp.h"

#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

std::vector<Point> generate_points(int N) {
    std::vector<Point> result;
    for (int i = 0; i < N; i++) {
        // Box-Muller transformation
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-1.0, 1.0);
        double x = 0;
        double y = 0;
        double s = 0;
        while (s > 1 || s == 0) {
            x = dis(gen);
            y = dis(gen);
            s = x * x + y * y;
        }
        double z0 = x * sqrt(-2 * log(s) / s);
        double z1 = y * sqrt(-2 * log(s) / s);
        result.emplace_back(Point{z0, z1});
    }
    return result;
}

double distance(const Point &p1, const Point &p2) {
    return sqrt((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
}

double row_mean(const std::vector<double> &row, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += row[i];

    return sum / n;
}

double row_std(const std::vector<double> &row, double mean, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += (row[i] - mean) * (row[i] - mean);

    return sqrt(sum / n);
}

void print_table(const std::vector<std::vector<double>> &table) {
    std::cout << "N\t\tTrial 1\t\tTrial 2\t\tTrial 3\t\tTrial 4\t\tTrial 5\t\tExact\t\tMean\t\tStd" << std::endl;
    std::cout << "---------------------------------------------------------------------"
              << "---------------------------------------------------------------------"
              << std ::endl;
    int N = 2;
    for (auto &row: table) {
        std::cout << N << "\t\t";
        N++;
        for (auto &elem: row) {
            std::cout << std::setprecision(5) << elem << "\t\t";
        }
        std::cout << std::endl;
    }
}

int main() {
    int no_of_trials = 5;
    std::vector<std::vector<double>> result_table;
    for (int N = 2; N < 11; N++) {
        std::vector<double> row;
        for (int k = 0; k < no_of_trials; k++) {
            auto points = generate_points(N);
            Graph g(N);
            for (int i = 0; i < N; i++) {
                for (int j = i + 1; j < N; j++) {
                    g.add_undirected_edge(i, j, distance(points[i], points[j]));
                }
            }
            row.push_back(PrimsApproximate(g));
            // append exact solution in the row
            if (k == no_of_trials - 1)
                row.push_back(Exact(g));
        }
        // calculate mean
        double mean = row_mean(row, no_of_trials);
        row.push_back(mean);
        // calculate standard deviation
        row.push_back(row_std(row, mean, no_of_trials));
        result_table.push_back(row);
    }

    print_table(result_table);

    return 0;
}