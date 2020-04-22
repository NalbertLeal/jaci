all:
	@mkdir -p bin/
	@g++ -Wall -g -O0 -std=c++17 -Iinclude/ src/main.cpp -o bin/main

