all: run

run: blackjack.o cardgame.o computer.o human.o eCash.o game.cpp
	g++ game.cpp blackjack.o cardgame.o computer.o human.o eCash.o -o run

blackjack.o: blackjack.cpp blackjack.h
	g++ -c blackjack.cpp

cardgame.o: cardgame.cpp cardgame.h
	g++ -c cardgame.cpp

computer.o: computer.cpp computer.h cardgame.h blackjack.h player.h
	g++ -c computer.cpp

human.o: human.cpp human.h cardgame.h blackjack.h player.h
	g++ -c human.cpp

eCash.o: eCash.cpp eCash.h human.h cardgame.h blackjack.h
	g++ -c eCash.cpp

clean:
	rm -f run *.o
