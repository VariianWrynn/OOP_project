all: run

run: 21point.o cardgame.o main.cpp
	g++ main.cpp 21point.o cardgame.o -o run

21point.o: 21point.cpp cardgame.h
	g++ -c 21point.cpp

cardgame.o: cardgame.cpp cardgame.h
	g++ -c cardgame.cpp

clean:
	rm -f run *.o
