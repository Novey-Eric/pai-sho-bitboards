
FLAGS := -I../include -g -Wall
GXX := g++

all: Computer.o Bitboard.o main.o
	$(GXX) ./build/main.o ./build/Bitboard.o ./build/Computer.o -o ./build/paisho $(FLAGS)

main.o: main.cpp
	$(GXX) -c main.cpp -o ./build/main.o $(FLAGS)
Computer.o: Computer.cpp
	$(GXX) -c Computer.cpp -o ./build/Computer.o $(FLAGS)
Bitboard.o: Bitboard.cpp
	$(GXX) -c Bitboard.cpp -o ./build/Bitboard.o $(FLAGS)
