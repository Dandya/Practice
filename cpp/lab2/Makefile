all: test-graph

test-graph:
	@g++ -std=c++20 ./test-graph.cpp -o test-graph -lgtest

run: test-graph
	@./test-graph
clean:
	@rm ./test-graph