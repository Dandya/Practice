#include "graph.h"

Graph::Graph() {}

Graph::Graph(std::vector<std::vector<bool>> adj_matrix) {
    m_adj_matrix = adj_matrix;
    m_count_nodes = adj_matrix.size();
    m_edge_weights.resize(m_count_nodes);
    for (int i = 0; i < m_count_nodes; i++) {
        if (m_adj_matrix[i].size() != m_count_nodes)
            throw std::invalid_argument(
                "Graph:all vectors in @adj_matrix must have same size.");
        m_edge_weights[i].resize(m_count_nodes, 0);
    }
}

Graph::Graph(std::vector<std::vector<bool>> adj_matrix,
             std::vector<std::vector<int>> edge_weights) {
    m_adj_matrix = adj_matrix;
    m_count_nodes = adj_matrix.size();
    m_edge_weights = edge_weights;
    bool check_sizes = m_count_nodes == m_edge_weights.size();
    for (int i = 0; i < m_count_nodes; ++i) {
        if (!check_sizes)
            throw std::invalid_argument(
                "Graph: @adj_matrix and @edge_weights must have same size.");
        check_sizes = m_adj_matrix[i].size() == m_edge_weights[i].size() &&
                      m_adj_matrix[i].size() == m_count_nodes;
    }
}

Graph::Graph(Graph &other) {
    m_adj_matrix = other.m_adj_matrix;
    m_count_nodes = other.m_adj_matrix.size();
}

Graph &Graph::operator=(Graph &other) {
    m_adj_matrix = other.m_adj_matrix;
    m_count_nodes = other.m_adj_matrix.size();
    return *this;
}

bool Graph::isUndirectedGraph() {
    for (int i = 0, j = 1; i < m_count_nodes; ++j) {
        if (j == m_count_nodes) {
            ++i;
            j = i + 1;
            if (i == m_count_nodes - 1)
                return true;
        }
        if (m_adj_matrix[i][j] != m_adj_matrix[j][i] ||
            m_edge_weights[i][j] != m_edge_weights[j][i]) {
            return false;
        }
    }
    return true;
}

bool Graph::isWeightsNotNegative() {
    for (int i = 0; i < m_count_nodes; ++i)
        for (int j = 0; j < m_count_nodes; ++j)
            if (m_edge_weights[i][j] < 0)
                return false;
    return true;
}

int Graph::getCountNodes() { return m_count_nodes; }

void Graph::createNodes(int count) {
    if (count <= 0)
        throw std::invalid_argument("createNodes: @count must be positive.");
    m_adj_matrix.resize(m_count_nodes + count);
    m_edge_weights.resize(m_count_nodes + count);
    for (int i = m_count_nodes; i < m_count_nodes + count; i++) {
        m_adj_matrix[i].resize(m_count_nodes + count, false);
        m_edge_weights[i].resize(m_count_nodes + count, 0);
    }
    m_count_nodes += count;
}

void Graph::addEdge(int from, int to, int weight) {
    if (from >= m_count_nodes || to >= m_count_nodes)
        throw std::invalid_argument(
            "addEdge: @from or @to equal or great than count of nodes.");
    m_adj_matrix[from][to] = true;
    m_edge_weights[from][to] = weight;
}

std::vector<std::vector<bool>> Graph::getAdjMatrix() { return m_adj_matrix; }

std::vector<std::vector<int>> Graph::getEdgeWeights() { return m_edge_weights; }

std::vector<int> Graph::DFS(int start_node) {
    if (!isUndirectedGraph())
        throw std::runtime_error("DFS: graph must be undirected.");
    if (start_node >= m_count_nodes)
        throw std::invalid_argument(
            "DFS: @start_node equal or great than count o nodes.");

    std::vector<int> result;
    std::stack<int> not_visited_nodes;
    std::vector<bool> visited_nodes(m_count_nodes);
    int node;

    not_visited_nodes.push(start_node);
    while (!not_visited_nodes.empty()) {
        node = not_visited_nodes.top();
        not_visited_nodes.pop();
        visited_nodes[node] = true;
        result.push_back(node);
        for (int i = m_count_nodes - 1; i >= 0; --i)
            if (m_adj_matrix[node][i] && !visited_nodes[i])
                not_visited_nodes.push(i);
    }
    return result;
}

std::vector<int> Graph::BFS(int start_node) {
    if (!isUndirectedGraph())
        throw std::runtime_error("BFS: graph must be undirected.");
    if (start_node >= m_count_nodes)
        throw std::invalid_argument(
            "BFS: @start_node equal or great than count o nodes.");

    std::vector<int> result;
    std::queue<int> not_visited_nodes;
    std::vector<bool> visited_nodes(m_count_nodes);
    int node;

    not_visited_nodes.push(start_node);
    while (!not_visited_nodes.empty()) {
        node = not_visited_nodes.front();
        not_visited_nodes.pop();
        visited_nodes[node] = true;
        result.push_back(node);
        for (int i = 0; i < m_count_nodes; ++i)
            if (m_adj_matrix[node][i] && !visited_nodes[i])
                not_visited_nodes.push(i);
    }

    return result;
}

std::vector<int> Graph::AlgDijkstra(int start_node) {
    if (!isUndirectedGraph())
        throw std::runtime_error("AlgDijkstra: graph must be undirected.");
    if (!isWeightsNotNegative())
        throw std::runtime_error(
            "AlgDijkstra: graph must have not negative weights of edges.");
    if (start_node >= m_count_nodes)
        throw std::invalid_argument(
            "AlgDijkstra: @start_node equal or great than count o nodes.");

    std::vector<int> shorted_paths;
    shorted_paths.resize(m_count_nodes, INT32_MAX);
    std::vector<bool> visited_nodes(m_count_nodes);

    shorted_paths[start_node] = 0;
    int index_min_path = start_node;
    for (int count_not_visited_nodes = m_count_nodes;
         count_not_visited_nodes > 0; --count_not_visited_nodes) {
        for (int i = 0; i < m_count_nodes; ++i)
            if (m_adj_matrix[index_min_path][i])
                if (shorted_paths[index_min_path] +
                        m_edge_weights[index_min_path][i] <
                    shorted_paths[i])
                    shorted_paths[i] = shorted_paths[index_min_path] +
                                       m_edge_weights[index_min_path][i];
        visited_nodes[index_min_path] = true;
        int index_path = 0;
        for (; index_path < m_count_nodes; ++index_path)
            if(!visited_nodes[index_path]) {
                index_min_path = index_path;
                ++index_path;
                break;
            }
        for (; index_path < m_count_nodes; ++index_path)
            if (!visited_nodes[index_path] && shorted_paths[index_path] <= shorted_paths[index_min_path])
                index_min_path = index_path;
    }
    return shorted_paths;
}

std::vector<std::vector<int>> Graph::AlgFloydWarshell() {
    if (!isUndirectedGraph())
        throw std::runtime_error("AlgFloydWarshell: graph must be undirected.");

    std::vector<std::vector<int>> result = m_edge_weights;

    //TODO: обработка для бесконечности

    for(int k = 0; k < m_count_nodes; ++k)
        for(int j = 0; j < m_count_nodes; ++j)
            for(int i = 0; i < m_count_nodes; ++i)
                if()
}