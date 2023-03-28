#include "graph.h"
#include "graph.cpp"
#include <gtest/gtest.h>
std::vector<std::vector<bool>>
    adj_matrix1({{true, false, true, false, true, true},
                 {false, false, true, false, false, false},
                 {true, true, false, true, false, false},
                 {false, false, true, false, false, false},
                 {true, false, false, false, false, false},
                 {true, false, false, false, false, true}});

std::vector<std::vector<bool>>
    adj_matrix2({{false, false, true, false, true, true},
                 {false, false, true, true, false, true},
                 {true, true, false, true, false, false},
                 {false, true, true, false, true, false},
                 {true, false, false, true, false, false},
                 {true, true, false, false, false, false}});

std::vector<std::vector<bool>>
    adj_matrix3({{false, false, true, true, true, true},
                 {false, false, true, false, false, true},
                 {true, true, false, false, false, false},
                 {true, false, false, false, true, false},
                 {true, false, false, true, false, false},
                 {true, true, false, false, false, false}});

std::vector<std::vector<bool>>
    adj_matrix4({{false, false, false, true, false, false, false, false},
                 {true, false, false, false, false, false, false, false},
                 {false, true, false, false, true, false, true, false},
                 {true, false, false, false, true, false, false, false},
                 {false, true, false, false, false, false, false, false},
                 {false, false, true, false, true, false, false, false},
                 {false, true, true, false, false, true, false, false},
                 {false, false, false, false, true, false, true, false}});


std::vector<std::vector<double>> edge_weights2({{0, 0, 3, 0, 2, 1},
                                                {0, 0, 4, 2, 0, 7},
                                                {3, 4, 0, 2, 0, 0},
                                                {0, 2, 2, 0, 5, 0},
                                                {2, 0, 0, 5, 0, 0},
                                                {1, 7, 0, 0, 0, 0}});

std::vector<std::vector<bool>>
    adj_matrix_undirected({{false, false, true, false, true, true},
                 {false, false, false, false, false, true},
                 {false, true, false, true, false, false},
                 {false, true, false, false, false, false},
                 {false, false, false, true, false, false},
                 {false, false, false, false, false, false}});

std::vector<std::vector<double>> edge_weights_undirected({{0, 0, 3, 0, 2, 1},
                                                {0, 0, 0, 0, 0, 7},
                                                {0, 4, 0, 2, 0, 0},
                                                {0, 2, 0, 0, 0, 0},
                                                {0, 0, 0, 5, 0, 0},
                                                {0, 0, 0, 0, 0, 0}});

TEST(Constructor, Default) {
    Graph graph;
    EXPECT_EQ(0, graph.getCountNodes());
}

TEST(CreateNodes, Node) {
    Graph graph;
    graph.createNodes(1);
    EXPECT_EQ(1, graph.getCountNodes());
}

TEST(CreateNodes, Nodes) {
    Graph graph;
    graph.createNodes(10);
    EXPECT_EQ(10, graph.getCountNodes());
}

TEST(CreateNodes, NodesWithEdge) {
    Graph graph;
    graph.createNodes(2);
    graph.addEdge(0, 1, 2);
    EXPECT_EQ(true, graph.getAdjMatrix()[0][1]);
    EXPECT_EQ(false, graph.getAdjMatrix()[0][0]);
    EXPECT_EQ(0, graph.getEdgeWeights()[0][0]);
}

TEST(Connectivity_components, emptyMatrix) {
    Graph graph;
    EXPECT_EQ(0, graph.getCountConnectivityComponents());
}

TEST(Connectivity_components, firstMatrix) {
    Graph graph(adj_matrix2);
    graph.removeEdge(0,4, true);
    graph.removeEdge(4,3, true);
    EXPECT_EQ(2, graph.getCountConnectivityComponents());
}


TEST(Connectivity_components, secondMatrix) {
    Graph graph(adj_matrix2);
    EXPECT_EQ(1, graph.getCountConnectivityComponents());
}

TEST(DFS, emptyMatrix) {
    Graph graph;
    try {
        EXPECT_EQ(1, graph.DFS(0).size());
    } catch (const std::invalid_argument &e) {
        EXPECT_TRUE(true);
    }
}

TEST(DFS, TestWork) {
    Graph graph(adj_matrix1);
    std::vector<int> true_result({0, 2, 1, 3, 4, 5});
    std::vector<int> result = graph.DFS(0);
    for (int i = 0; i < graph.getCountNodes(); ++i) {
        EXPECT_EQ(true_result[i], result[i]);
    }
}

TEST(BFS, emptyMatrix) {
    Graph graph;
    try {
        EXPECT_EQ(1, graph.BFS(0).size());
    } catch (const std::invalid_argument &e) {
        EXPECT_TRUE(true);
    }
}

TEST(BFS, TestWork) {
    Graph graph(adj_matrix1);
    std::vector<int> true_result({0, 2, 4, 5, 1, 3});
    std::vector<int> result = graph.BFS(0);
    for (int i = 0; i < graph.getCountNodes(); ++i) {
        EXPECT_EQ(true_result[i], result[i]);
    }
}

TEST(DijkstraAlgorithm, emptyMatrix) {
    Graph graph;
    try {
        EXPECT_EQ(1, graph.AlgDijkstra(0).size());
    } catch (const std::invalid_argument &e) {
        EXPECT_TRUE(true);
    }
}

TEST(DijkstraAlgorithm, notPositiveMatrix) {
    std::vector<std::vector<double>> cp_edge_weights = edge_weights2;
    cp_edge_weights[0][1] = -1;
    cp_edge_weights[1][0] = -1;
    Graph graph(adj_matrix2, edge_weights2);
    try {
        EXPECT_EQ(6, graph.AlgDijkstra(0).size());
    } catch (const std::runtime_error &e) {
        EXPECT_TRUE(true);
    }
}

TEST(DijkstraAlgorithm, TestWork) {
    Graph graph(adj_matrix2, edge_weights2);
    std::vector<double> true_result({0, 7, 3, 5, 2, 1});
    std::vector<double> result = graph.AlgDijkstra(0);
    for (int i = 0; i < graph.getCountNodes(); ++i) {
        EXPECT_EQ(true_result[i], result[i]);
    }
}

TEST(AlgorithmFloydWarshell, emptyMatrix) {
    Graph graph;
    EXPECT_EQ(0, graph.AlgFloydWarshell().size());
}

TEST(AlgorithmFloydWarshell, TestWork) {
    Graph graph(adj_matrix2, edge_weights2);
    std::vector<std::vector<double>> true_result({{0, 7, 3, 5, 2, 1},
                                                  {7, 0, 4, 2, 7, 7},
                                                  {3, 4, 0, 2, 5, 4},
                                                  {5, 2, 2, 0, 5, 6},
                                                  {2, 7, 5, 5, 0, 3},
                                                  {1, 7, 4, 6, 3, 0}});
    std::vector<std::vector<double>> result = graph.AlgFloydWarshell();
    for (int i = 0; i < graph.getCountNodes(); ++i)
        for (int j = 0; j < graph.getCountNodes(); ++j)
            EXPECT_EQ(true_result[i][j], result[i][j]);
}

TEST(AlgorithmFloydWarshell, TestWorkNegativeCircle) {
    std::vector<std::vector<double>> edge_weights_tmp({{0, 0, 3, 0, 2, 1},
                                                {0, 0, 4, -10, 0, 7},
                                                {3, 4, 0, 2, 0, 0},
                                                {0, -10, 2, 0, 5, 0},
                                                {2, 0, 0, 5, 0, 0},
                                                {1, 7, 0, 0, 0, 0}});
    Graph graph(adj_matrix2, edge_weights_tmp);
    try{
        std::vector<std::vector<double>> result = graph.AlgFloydWarshell();
        EXPECT_TRUE(false);
    } catch(std::runtime_error e) {
        if(std::string(e.what()) == std::string("Graph has negative circle."))
            EXPECT_TRUE(true);
        else
            EXPECT_TRUE(false);
    }
}

TEST(AlgorithmPrim, emptyMatrix) {
    Graph graph;
    try {
        EXPECT_EQ(1, graph.AlgPrim(0).size());
    } catch (const std::invalid_argument &e) {
        EXPECT_TRUE(true);
    }
}

TEST(AlgorithmPrim, TestWork) {
    Graph graph(adj_matrix2, edge_weights2);
    std::vector<std::vector<int>> true_result(
        {{3, 1}, {0, 2}, {2, 3}, {0, 4}, {0, 5}});
    std::vector<std::vector<int>> result = graph.AlgPrim(0);
    for (int i = 0; i < true_result.size(); i++) 
        EXPECT_EQ(true_result[i], result[i]);
}

TEST(AlgorithmKruskal, getEdges) {
    Graph graph(adj_matrix2, edge_weights2);
    std::vector<std::vector<int>> true_result(
        { {0,2}, {0,4}, {0,5}, {1,2}, {1,3}, {1,5}, {2,3}, {3,4}});
    std::vector<std::vector<int>> result = graph.getVectorOfEdges();
    for (int i = 0; i < true_result.size(); i++) 
        EXPECT_EQ(true_result[i], result[i]);
}

TEST(AlgorithmKruskal, emptyMatrix) {
    Graph graph;
    EXPECT_EQ(0, graph.AlgKruskal().size());
}

TEST(AlgorithmKruskal, TestWork) {
    Graph graph(adj_matrix2, edge_weights2);
    std::vector<std::vector<int>> true_result(
        {{0,5}, {0,4}, {1,3}, {2,3}, {0,2}});
    std::vector<std::vector<int>> result = graph.AlgKruskal();
    for (int i = 0; i < true_result.size(); i++) 
        EXPECT_EQ(true_result[i], result[i]);
}

TEST(AlgorithmTarjan, emptyMatrix) {
    Graph graph;
    EXPECT_EQ(0, graph.AlgTarjan().size());
}

TEST(AlgorithmTarjan, TestWork) {
    Graph graph(adj_matrix_undirected, edge_weights_undirected);
    std::vector<int> true_result(
        {0,4,2,3,1,5});
    std::vector<int> result = graph.AlgTarjan();
    for (int i = 0; i < true_result.size(); i++) 
        EXPECT_EQ(true_result[i], result[i]);
}

TEST(AlgorithmTarjan, TestWorkWithCircle) {
    Graph graph(adj_matrix_undirected, edge_weights_undirected);
    graph.addEdge(1,2,0);
    try{
        std::vector<int> result = graph.AlgTarjan();
        EXPECT_TRUE(false);
    } catch(std::runtime_error e) {
        if(std::string(e.what()) == std::string("AlgTarjan: graph has circles."))
            EXPECT_TRUE(true);
        else
            EXPECT_TRUE(false);
    }
}

TEST(AlgorithmFleury, emptyMatrix) {
    Graph graph;
    EXPECT_EQ(0, graph.AlgFleury().size());
}

TEST(AlgorithmFleury, TestWork) {
    Graph graph(adj_matrix3);
    std::vector<std::vector<int>> true_result({ std::vector({0,2}), std::vector<int>({2,1}), std::vector<int>({1,5}), std::vector<int>({5,0}), std::vector<int>({0,3}), std::vector<int>({3,4}), std::vector<int>({4,0}) });
    std::vector<std::vector<int>> result = graph.AlgFleury();
    for (int i = 0; i < true_result.size(); i++) 
        EXPECT_EQ(true_result[i], result[i]);
}



TEST(AlgorithmOnCircles, emptyMatrix) {
    Graph graph;
    EXPECT_EQ(0, graph.findEulerCircle().size());
}

TEST(AlgorithmOnCircles, TestWork) {
    Graph graph(adj_matrix3);
    std::vector<int> true_result({0, 4, 3, 0, 5, 1, 2, 0});
    std::vector<int> result = graph.findEulerCircle();
    EXPECT_EQ(true_result, result);
    for (int i = 0; i < true_result.size(); i++) 
        EXPECT_EQ(true_result[i], result[i]);
}

TEST(AlgorithmKosaraju, emptyMatrix) {
    Graph graph;
    EXPECT_EQ(0, graph.AlgKosaraju().size());
}

TEST(AlgorithmKosaraju, TestWork) {
    Graph graph(adj_matrix4);
    std::vector<std::vector<int>> true_result({{1,4,3,0}, {5,6,2}, {7}});
    std::vector<std::vector<int>> result = graph.AlgKosaraju();
    EXPECT_EQ(true_result, result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}