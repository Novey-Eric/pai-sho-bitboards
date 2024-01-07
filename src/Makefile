
FLAGS := -I../include -O1 -g -Wall 

all: Computer.o Bitboard.o main.o
	g++ ./build/main.o ./build/Bitboard.o ./build/Computer.o -o ./build/paisho $(FLAGS)

main.o: main.cpp
	g++ -c main.cpp -o ./build/main.o $(FLAGS)
Computer.o: Computer.cpp
	g++ -c Computer.cpp -o ./build/Computer.o $(FLAGS)
Bitboard.o: Bitboard.cpp
	g++ -c Bitboard.cpp -o ./build/Bitboard.o $(FLAGS)
