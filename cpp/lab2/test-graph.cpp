#include "graph.cpp"
#include "graph.h"
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

std::vector<std::vector<int>> edge_weights2({{0, 0, 3, 0, 2, 1},
                                            {0, 0, 4, 2, 0, 7},
                                            {3, 4, 0, 2, 0, 0},
                                            {0, 2, 2, 0, 5, 0},
                                            {2, 0, 0, 5, 0, 0},
                                            {1, 7, 0, 0, 0, 0}});

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
    std::vector<std::vector<int>> cp_edge_weights = edge_weights2;
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
    std::vector<int> true_result({0,7,3,5,2,1});
    std::vector<int> result = graph.AlgDijkstra(0);
    for (int i = 0; i < graph.getCountNodes(); ++i) {
        EXPECT_EQ(true_result[i], result[i]);
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}