all: test-graph

test-graph:
	@g++ ./test-graph.cpp -o test-graph -lgtest

run: test-graph
	@./test-graph
clean:
	@rm ./test-graph