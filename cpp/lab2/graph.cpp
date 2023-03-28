#include "graph.h"

// TODO: change check on right start_node in DFS and BFS
// ! lab 5a

Graph::Graph() {}

Graph::Graph(std::vector<std::vector<bool>> adj_matrix) {
    m_adj_matrix = adj_matrix;
    m_count_nodes = adj_matrix.size();
    if (checkExceedingMaxCountNodes())
        throw std::runtime_error("Graph: Exceeding of мax count nodes.");
    m_edge_weights.resize(m_count_nodes);
    for (int i = 0; i < m_count_nodes; i++) {
        if (m_adj_matrix[i].size() != m_count_nodes)
            throw std::invalid_argument(
                "Graph:all vectors in @adj_matrix must have same size.");
        m_edge_weights[i].resize(m_count_nodes, 0);
    }
}

Graph::Graph(std::vector<std::vector<bool>> adj_matrix,
             std::vector<std::vector<double>> edge_weights) {
    m_adj_matrix = adj_matrix;
    m_count_nodes = adj_matrix.size();
    if (checkExceedingMaxCountNodes())
        throw std::runtime_error("Graph: Exceeding of мax count nodes.");
    m_edge_weights = edge_weights;
    bool check_sizes = m_count_nodes == m_edge_weights.size();
    for (int i = 0; i < m_count_nodes; i++) {
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
    m_edge_weights = other.m_edge_weights;
}

Graph &Graph::operator=(Graph &other) {
    m_adj_matrix = other.m_adj_matrix;
    m_count_nodes = other.m_adj_matrix.size();
    m_edge_weights = other.m_edge_weights;
    return *this;
}

bool Graph::checkExceedingMaxCountNodes() { return m_count_nodes < 0; }

bool Graph::isUndirectedGraph() {
    for (int i = 0, j = 1; i < m_count_nodes; j++) {
        if (j == m_count_nodes) {
            i++;
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

bool Graph::hasPositiveWeights() {
    for (int i = 0; i < m_count_nodes; i++)
        for (int j = 0; j < m_count_nodes; j++)
            if (m_edge_weights[i][j] < 0)
                return false;
    return true;
}

int Graph::getCountNodes() { return m_count_nodes; }

void Graph::createNodes(int count) {
    if (count <= 0)
        throw std::invalid_argument("createNodes: @count must be positive.");
    if (m_count_nodes + count < 0)
        throw std::runtime_error("createNodes: Exceeding of мax count nodes.");

    m_adj_matrix.resize(m_count_nodes + count);
    m_edge_weights.resize(m_count_nodes + count);
    for (int i = m_count_nodes; i < m_count_nodes + count; i++) {
        m_adj_matrix[i].resize(m_count_nodes + count, false);
        m_edge_weights[i].resize(m_count_nodes + count, 0);
    }
    m_count_nodes += count;
}

void Graph::addEdge(int from, int to, int weight) {
    if (from >= m_count_nodes || to >= m_count_nodes || from < 0 || to < 0)
        throw std::invalid_argument(
            "addEdge: @from or @to equal or great than count of nodes.");
    m_adj_matrix[from][to] = true;
    m_edge_weights[from][to] = weight;
}

std::vector<std::vector<bool>> Graph::getAdjMatrix() { return m_adj_matrix; }

std::vector<std::vector<double>> Graph::getEdgeWeights() {
    return m_edge_weights;
}

std::vector<std::vector<int>> Graph::getVectorOfEdges() {
    if (!isUndirectedGraph())
        throw std::runtime_error("getVectorOfEdges: graph must be undirected.");

    std::vector<std::vector<int>> result;
    for (int i = 0; i < m_count_nodes; i++)
        for (int j = i + 1; j < m_count_nodes; j++)
            if (m_adj_matrix[i][j])
                result.push_back(std::vector<int>({i, j}));

    return result;
}

bool Graph::compareEdges(std::vector<int> &l_from_to_nodes,
                         std::vector<int> &r_from_to_nodes) {
    return m_edge_weights[l_from_to_nodes[0]][l_from_to_nodes[1]] <
           m_edge_weights[r_from_to_nodes[0]][r_from_to_nodes[1]];
}

void Graph::sortVectorEdges(std::vector<std::vector<int>> &edges) {
    bool was_sort = true;
    while (was_sort) {
        was_sort = false;
        for (int i = 1; i < edges.size(); i++) {
            if (compareEdges(edges[i], edges[i - 1])) {
                std::swap(edges[i], edges[i - 1]);
                was_sort = true;
            }
        }
    }
}

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
        for (int i = 0; i < m_count_nodes; i++)
            if (m_adj_matrix[node][i] && !visited_nodes[i])
                not_visited_nodes.push(i);
    }

    return result;
}

std::vector<double> Graph::AlgDijkstra(int start_node) {
    if (!isUndirectedGraph())
        throw std::runtime_error("AlgDijkstra: graph must be undirected.");
    if (!hasPositiveWeights())
        throw std::runtime_error(
            "AlgDijkstra: graph must have not negative weights of edges.");
    if (start_node >= m_count_nodes)
        throw std::invalid_argument(
            "AlgDijkstra: @start_node equal or great than count o nodes.");

    std::vector<double> shorted_paths;
    shorted_paths.resize(m_count_nodes, INT32_MAX);
    std::vector<bool> visited_nodes(m_count_nodes);

    shorted_paths[start_node] = 0;
    int index_min_path = start_node;
    for (int count_not_visited_nodes = m_count_nodes;
         count_not_visited_nodes > 0; --count_not_visited_nodes) {
        for (int i = 0; i < m_count_nodes; i++)
            if (m_adj_matrix[index_min_path][i])
                if (shorted_paths[index_min_path] +
                        m_edge_weights[index_min_path][i] <
                    shorted_paths[i])
                    shorted_paths[i] = shorted_paths[index_min_path] +
                                       m_edge_weights[index_min_path][i];
        visited_nodes[index_min_path] = true;
        int index_path = 0;
        for (; index_path < m_count_nodes; index_path++)
            if (!visited_nodes[index_path]) {
                index_min_path = index_path;
                index_path++;
                break;
            }
        for (; index_path < m_count_nodes; index_path++)
            if (!visited_nodes[index_path] &&
                shorted_paths[index_path] <= shorted_paths[index_min_path])
                index_min_path = index_path;
    }
    return shorted_paths;
}

std::vector<std::vector<double>> Graph::AlgFloydWarshell() {
    if (!isUndirectedGraph())
        throw std::runtime_error("AlgFloydWarshell: graph must be undirected.");

    std::vector<std::vector<double>> result = m_edge_weights;
    std::vector<std::vector<int>> vec_last_nodes(m_count_nodes);

    for (int i = 0; i < m_count_nodes; i++) {
        vec_last_nodes[i].resize(m_count_nodes);
        for (int j = 0; j < m_count_nodes; j++) {
            if (!m_adj_matrix[i][j] && i != j) {
                result[i][j] = std::numeric_limits<double>::infinity();
                vec_last_nodes[i][j] = m_count_nodes;
            } else if (m_adj_matrix[i][j]) {
                vec_last_nodes[i][j] = i;
            } else {
                vec_last_nodes[i][i] = i;
            }
        }
    }

    for (int k = 0; k < m_count_nodes; k++) {
        for (int j = 0; j < m_count_nodes; j++) {
            if (result[j][k] == std::numeric_limits<double>::infinity())
                continue;
            for (int i = 0; i < m_count_nodes; i++) {
                if (result[i][j] > result[i][k] + result[k][j]) {
                    result[i][j] = result[i][k] + result[k][j];
                    vec_last_nodes[i][j] = vec_last_nodes[k][j];
                }
            }
        }

        for (int i = 0; i < m_count_nodes; i++)
            if (result[i][i] < 0)
                throw std::runtime_error("Graph has negative circle.");
    }

    for (int i = 0; i < m_count_nodes; i++) {
        std::cout << "|";
        for (int j = 0; j < m_count_nodes; j++) {
            std::cout << std::to_string(i) << std::string("-")
                      << std::to_string(j) << std::string(":")
                      << std::to_string(vec_last_nodes[i][j])
                      << std::string("|");
        }
        std::cout << std::endl;
    }
    return result;
}

int Graph::getNodeWithMinWeight(std::vector<int> &nodes,
                                std::vector<double> &weights) {
    int min_node = nodes[0];
    for (int node : nodes)
        if (weights[min_node] > weights[node])
            min_node = node;
    return min_node;
}

std::vector<std::vector<int>> Graph::AlgPrim(int start_node) {
    if (!isUndirectedGraph())
        throw std::runtime_error("AlgPrim: graph must be undirected.");
    if (start_node >= m_count_nodes)
        throw std::invalid_argument(
            "AlgPrim: @start_node equal or great than count o nodes.");

    std::vector<double> min_lengths(m_count_nodes,
                                    std::numeric_limits<double>::infinity());
    std::vector<int> parents(m_count_nodes, -1);
    std::vector<int> not_visited_nodes;
    for (int i = 0; i < m_count_nodes; i++)
        not_visited_nodes.push_back(i);
    std::vector<bool> visited_flags(m_count_nodes, false);

    min_lengths[start_node] = 0;
    while (!not_visited_nodes.empty()) {
        int node = getNodeWithMinWeight(not_visited_nodes, min_lengths);
        for (int i = 0; i < m_count_nodes; i++) {
            if (m_adj_matrix[node][i]) {
                if (min_lengths[i] > m_edge_weights[node][i] &&
                    visited_flags[i] == false) {
                    min_lengths[i] = m_edge_weights[node][i];
                    parents[i] = node;
                }
            }
        }
        std::erase(not_visited_nodes, node);
        visited_flags[node] = true;
    }

    std::vector<std::vector<int>> result;
    for (int i = 0; i < m_count_nodes; i++)
        if (i != start_node)
            result.push_back(std::vector<int>({parents[i], i}));

    return result;
}

std::vector<std::vector<int>> Graph::AlgKruskal() {
    if (!isUndirectedGraph())
        throw std::runtime_error("AlgKruskal: graph must be undirected.");

    std::vector<std::vector<int>> result;
    std::vector<int> flags_of_including_tree(m_count_nodes);
    for (int i = 0; i < m_count_nodes; i++)
        flags_of_including_tree[i] = i;
    std::vector<std::vector<int>> vector_edges = getVectorOfEdges();
    sortVectorEdges(vector_edges);

    for (std::vector<int> edge : vector_edges) {
        if (flags_of_including_tree[edge[0]] !=
            flags_of_including_tree[edge[1]]) {
            result.push_back(edge);
            int tmp = flags_of_including_tree[edge[0]];
            for (int i = 0; i < m_count_nodes; i++) {
                if (flags_of_including_tree[i] == tmp) {
                    flags_of_including_tree[i] =
                        flags_of_including_tree[edge[1]];
                }
            }
        }
    }

    return result;
}

// ! lab 5b

bool Graph::isIncludedNodeInVector(int node,
                                   std::vector<int> &vector_with_nodes) {
    for (int i = 0; i < vector_with_nodes.size(); i++)
        if (node == vector_with_nodes[i])
            return true;
    return false;
}

void Graph::AlgTarjan_dfs_inv(int parent_node,
                              std::vector<bool> &flags_visited_nodes,
                              std::stack<int> &visited_nodes,
                              std::vector<int> parents_nodes) {

    flags_visited_nodes[parent_node] = true;
    for (int children_node = 0; children_node < m_count_nodes; children_node++)
        if (m_adj_matrix[parent_node][children_node])
            if (!flags_visited_nodes[children_node]) {
                parents_nodes.push_back(parent_node);
                AlgTarjan_dfs_inv(children_node, flags_visited_nodes,
                                  visited_nodes, parents_nodes);
            } else if (isIncludedNodeInVector(children_node, parents_nodes))
                throw std::runtime_error("AlgTarjan: graph has circles.");

    visited_nodes.push(parent_node);
}

std::vector<int> Graph::AlgTarjan() {

    std::vector<bool> flags_visited_nodes(m_count_nodes);
    std::vector<int> parents_nodes;
    std::stack<int> visited_nodes;

    for (int node = 0; node < m_count_nodes; node++) {
        if (flags_visited_nodes[node] == false) {
            AlgTarjan_dfs_inv(node, flags_visited_nodes, visited_nodes,
                              parents_nodes);
        }
    }

    std::vector<int> result;
    result.resize(m_count_nodes);
    for (int i = 0; i < m_count_nodes; i++) {
        result[i] = visited_nodes.top();
        visited_nodes.pop();
    }

    return result;
}

int Graph::getCountEdges() {
    int count = 0;
    for (int from = 0; from < m_count_nodes; from++) {
        for (int to = 0; to < m_count_nodes; to++) {
            if (m_adj_matrix[from][to]) {
                count++;
            }
        }
    }
    return count;
}

int Graph::getCountEdgesFromNode(int from) {
    int count = 0;
    for (int to = 0; to < m_count_nodes; to++) {
        if (m_adj_matrix[from][to]) {
            count++;
        }
    }
    return count;
}

void Graph::removeEdge(int from, int to, bool is_undirected) {
    m_adj_matrix[from][to] = false;
    m_edge_weights[from][to] = 0;
    if (is_undirected) {
        m_adj_matrix[to][from] = false;
        m_edge_weights[to][from] = 0;
    }
}

void Graph::dfs(int parent_node, std::vector<bool> &flags_visited_nodes,
                std::stack<int> &visited_nodes) {

    flags_visited_nodes[parent_node] = true;
    for (int children_node = 0; children_node < m_count_nodes; children_node++)
        if (m_adj_matrix[parent_node][children_node])
            if (!flags_visited_nodes[children_node]) {
                dfs(children_node, flags_visited_nodes, visited_nodes);
            }

    visited_nodes.push(parent_node);
}

int Graph::getCountConnectivityComponents() {

    std::vector<bool> flags_visited_nodes(m_count_nodes);
    std::stack<int> visited_nodes;
    int count_connectivity_components = 0;
    for (int node = 0; node < m_count_nodes; node++) {
        if (flags_visited_nodes[node] == false) {
            count_connectivity_components++;
            dfs(node, flags_visited_nodes, visited_nodes);
        }
    }

    return count_connectivity_components;
}

bool Graph::isEvenGraph() {
    for (int node = 0; node < m_count_nodes; node++) {
        int count_edges = 0;
        for (int i = 0; i < m_count_nodes; i++) {
            if (m_adj_matrix[node][i]) {
                if (node != i) {
                    count_edges++;
                } else {
                    count_edges += 2;
                }
            }
        }
        if (count_edges % 2 != 0) {
            return false;
        }
    }
    return true;
}

std::vector<std::vector<int>> Graph::AlgFleury() {
    if (getCountEdges() == 0) {
        return std::vector<std::vector<int>>(0);
    }
    if (!isUndirectedGraph()) {
        throw std::runtime_error("AlgFleury: graph must be undirected.");
    }
    if (getCountConnectivityComponents() != 1) {
        throw std::runtime_error(
            "AlgFleury: graph must has one connectivity component.");
    }
    if (!isEvenGraph()) {
        throw std::runtime_error("AlgFleury: graph must has even nodes.");
    }

    std::vector<std::vector<int>> result;
    Graph graph_copy = *this;
    int node = 0;
    while (graph_copy.getCountEdges() > 0) {
        for (int i = 0; i < m_count_nodes; i++) {
            if(graph_copy.m_adj_matrix[node][i]) {
                int count_connectivity_components =
                    graph_copy.getCountConnectivityComponents();
                graph_copy.removeEdge(node, i, true);
                if (graph_copy.getCountConnectivityComponents() ==
                        count_connectivity_components ||
                    getCountEdgesFromNode(node) == 0) {
                    result.push_back(std::vector<int>({node, i}));
                    //std::cout << std::string("edge: (") + std::to_string(node) + std::string(",") + std::to_string(i) + std::string(")\n");
                    node = i;
                    break;
                }
                graph_copy.addEdge(node, i, 1);
            }
        }
    }
    return result;
}

void Graph::findEulerCircle_recursive(Graph& graph, int node, std::vector<int> &result) {
    for(int to = 0; to < m_count_nodes; to++) {
        if(graph.m_adj_matrix[node][to]) {
            graph.removeEdge(node, to, true);
            findEulerCircle_recursive(graph, to, result);
        }
    }
    result.push_back(node);
}

std::vector<int> Graph::findEulerCircle() {
    if (getCountEdges() == 0) {
        return std::vector<int>(0);
    }
    if (!isUndirectedGraph()) {
        throw std::runtime_error("AlgFleury: graph must be undirected.");
    }
    if (getCountConnectivityComponents() != 1) {
        throw std::runtime_error(
            "AlgFleury: graph must has one connectivity component.");
    }
    if (!isEvenGraph()) {
        throw std::runtime_error("AlgFleury: graph must has even nodes.");
    }

    std::vector<int> result;
    Graph graph_copy = *this;
    findEulerCircle_recursive(graph_copy, 0, result);

    return result;
}