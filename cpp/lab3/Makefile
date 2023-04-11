all: test-map

test-map:
	@g++ -std=c++20 ./test-map.cpp -o test-map -lgtest

run: test-map
	@./test-map
clean:
	@rm ./test-map