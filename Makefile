FLAGS = -pedantic-errors -std=c++11

clear.o: clear.cpp clear.h
	g++ -c clear.cpp

frame.o: frame.cpp frame.h
	g++ -c frame.cpp -lncurses

invader.o: invader.cpp invader.h
	g++ -c invader.cpp

shot.o: shot.cpp shot.h
	g++ -c shot.cpp

player.o: player.cpp player.h
	g++ -c player.cpp

endgame.o: endgame.cpp endgame.h
	g++ -c endgame.cpp

invaders.o: main.cpp
	g++ -c main.cpp -lncurses

invaders: clear.o frame.o invader.o endgame.o player.o shot.o main.o
	g++ clear.o frame.o invader.o player.o shot.o endgame.o main.o -o invaders -lncurses

clean:
	rm -f invaders *.o

.PHONY: clean