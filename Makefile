FLAGS = -pedantic-errors -std=c++11

clear.o: clear.cpp clear.h
	g++ -c clear.cpp

frame.o: frame.cpp frame.h
	g++ -c frame.cpp

invaders.o: main.cpp clear.h frame.h
	g++ -c main.cpp

invaders: clear.o frame.o main.o
	g++ clear.o frame.o main.o -o invaders

clean:
	rm -f invaders main.o clear.o frame.o

.PHONY: clean