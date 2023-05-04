FLAGS = -pedantic-errors -std=c++11

lib.o: lib.cpp lib.h
	g++ -c lib.cpp -lncursesw

frame.o: frame.cpp frame.h
	g++ -c frame.cpp -lncursesw

invader.o: invader.cpp invader.h
	g++ -c invader.cpp

shot.o: shot.cpp shot.h
	g++ -c shot.cpp

player.o: player.cpp player.h
	g++ -c player.cpp

invaders.o: main.cpp
	g++ -c main.cpp -lncursesw

invaders: frame.o invader.o player.o shot.o lib.o main.o
	g++ frame.o invader.o player.o shot.o lib.o main.o -o invaders -lncursesw

clean:
	rm -f invaders *.o

.PHONY: clean