
FLAGS := -I../include -g -Wall

all: Computer.o Bitboard.o
	g++ main.cpp ./build/Computer.o ./build/Bitboard.o -o ./build/paisho $(FLAGS)

Computer.o: Computer.cpp
	g++ -c Computer.cpp -o ./build/Computer.o $(FLAGS)
Bitboard.o: Bitboard.cpp
	g++ -c Bitboard.cpp -o ./build/Bitboard.o $(FLAGS)
