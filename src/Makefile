
FLAGS := -I../include -g -Wall -std=c++20 
CXX := g++

build/paisho: build/Computer.o build/Bitboard.o build/main.o
	$(CXX) $^ -o $@ $(FLAGS)

build/main.o: main.cpp
	$(CXX) -c $^ -o $@ $(FLAGS)
build/Computer.o: Computer.cpp
	$(CXX) -c $^ -o $@ $(FLAGS)
build/Bitboard.o: Bitboard.cpp
	$(CXX) -c $^ -o $@ $(FLAGS)
