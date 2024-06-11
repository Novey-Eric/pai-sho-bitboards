
FLAGS := -I../include -g -Wall -std=c++20 
CXX := g++

build/paisho: build/Computer.o build/Bitboard.o build/main.o
	$(CXX) $^ -o $@ $(FLAGS)

build/main.o: main.cpp ../include/Computer.h ../include/types.h ../include/Bitboard.h
	$(CXX) -c $< -o $@ $(FLAGS)
build/Computer.o: Computer.cpp ../include/Computer.h ../include/types.h
	$(CXX) -c $< -o $@ $(FLAGS)
build/Bitboard.o: Bitboard.cpp ../include/Bitboard.h ../include/types.h
	$(CXX) -c $< -o $@ $(FLAGS)

clean:
	rm build/*