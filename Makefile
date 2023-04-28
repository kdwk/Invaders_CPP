FLAGS = -pedantic-errors -std=c++11

later.o: later.cpp later.h
	g++ -c later.cpp

clear.o: clear.cpp clear.h
	g++ -c clear.cpp

frame.o: frame.cpp frame.h
	g++ -c frame.cpp

invader.o: invader.cpp invader.h
	g++ -c invader.cpp

invaders.o: main.cpp
	g++ -c main.cpp

invaders: clear.o frame.o later.o invader.o main.o
	g++ clear.o frame.o later.o main.o -o invaders

clean:
	rm -f invaders *.o

.PHONY: clean