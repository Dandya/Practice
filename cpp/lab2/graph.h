#ifndef GRAPH_H

#define GRAPH_H
#include <algorithm> // for std::sort and std::search
#include <iostream>
#include <limits>
#include <queue>
#include <stack>
#include <vector>

class Graph
{
private:
    std::vector<std::vector<bool>> m_adj_matrix;
    std::vector<std::vector<double>> m_edge_weights;
    int m_count_nodes = 0;

    // lab 5a
    bool checkExceedingMaxCountNodes();
    int getNodeWithMinWeight(std::vector<int> &nodes,
                             std::vector<double> &weights);
    bool compareEdges(std::vector<int> &l_from_to_nodes,
                      std::vector<int> &r_from_to_nodes);
    void sortVectorEdges(std::vector<std::vector<int>> &edges);

    // lab 5b
    bool isIncludedNodeInVector(int node, std::vector<int> &vector_with_nodes);
    void AlgTarjan_dfs_inv(int start_node,
                           std::vector<bool> &flags_visited_nodes,
                           std::stack<int> &visited_nodes, std::vector<int> parents_nodes);
    void dfs(int parent_node, std::vector<bool> &flags_visited_nodes, std::stack<int> &visited_nodes);
    //void dfs_inv(int parent_node, std::vector<bool> &flags_visited_nodes, std::stack<int> &visited_nodes);
    bool isEvenGraph();
    void findEulerCircle_recursive(Graph &graph, int node, std::vector<int> &result);

public:
    Graph();

    Graph(std::vector<std::vector<bool>> adj_matrix);

    Graph(std::vector<std::vector<bool>> adj_matrix,
          std::vector<std::vector<double>> edge_weights);

    Graph(Graph &other);

    Graph &operator=(Graph &other);

    bool isUndirectedGraph();

    bool hasPositiveWeights();

    int getCountNodes();

    int getCountEdges();

    int getCountEdgesFromNode(int from);

    int getCountConnectivityComponents();

    void createNodes(int count);

    void addEdge(int from, int to, int weight);

    void removeEdge(int from, int to, bool is_undirected);

    std::vector<std::vector<bool>> getAdjMatrix();

    std::vector<std::vector<double>> getEdgeWeights();

    std::vector<std::vector<int>> getVectorOfEdges();

    // difficulty: O(|E| + |V|)
    std::vector<int> DFS(int node);

    // difficulty: O(|E| + |V|)
    std::vector<int> BFS(int node);

    // difficulty: O(|V|^2)
    std::vector<double> AlgDijkstra(int start_node);

    // difficulty: O(|V|^3)
    std::vector<std::vector<double>> AlgFloydWarshell();

    // difficulty: O(|V|^2)
    std::vector<std::vector<int>> AlgPrim(int start_node);

    // difficulty: O(|E|^2)
    std::vector<std::vector<int>> AlgKruskal();

    // difficulty: O(|E| + |V|)
    std::vector<int> AlgTarjan();

    std::vector<std::vector<int>> AlgFleury();

    std::vector<int> findEulerCircle();

    std::vector<std::vector<int>> AlgKosaraju();
};

#endif