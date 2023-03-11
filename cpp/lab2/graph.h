#ifndef GRAPH_H

#define GRAPH_H
#include <iostream>
#include <queue>
#include <stack>
#include <vector>

class Graph {
  private:
    std::vector<std::vector<bool>> m_adj_matrix;
    std::vector<std::vector<int>> m_edge_weights;
    int m_count_nodes = 0;

  public:
    Graph();

    Graph(std::vector<std::vector<bool>> adj_matrix);

    Graph(std::vector<std::vector<bool>> adj_matrix,
          std::vector<std::vector<int>> edge_weights);

    Graph(Graph &other);

    Graph &operator=(Graph &other);

    bool isUndirectedGraph();

    bool isWeightsNotNegative();

    int getCountNodes();

    void createNodes(int count);

    void addEdge(int from, int to, int weight);

    std::vector<std::vector<bool>> getAdjMatrix();

    std::vector<std::vector<int>> getEdgeWeights();

    std::vector<int> DFS(int node);

    std::vector<int> BFS(int node);

    std::vector<int> AlgDijkstra(int start_node);

    std::vector<std::vector<int>> AlgFloydWarshell();
};

#endif