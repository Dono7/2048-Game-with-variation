
all: GAME_LAUNCHER

GAME_LAUNCHER: 2048main.o fonctionsStructureMinimale.o
	g++ 2048main.o fonctionsStructureMinimale.o -o GAME_LAUNCHER -lncurses
	rm *.o

2048main.o: 2048main.cpp fonctionsStructureMinimale.h
	g++ -c -std=c++11 2048main.cpp -lncurses

fonctionsStructureMinimale.o: fonctionsStructureMinimale.cpp fonctionsStructureMinimale.h
	g++ -c -std=c++11 fonctionsStructureMinimale.cpp -lncurses



