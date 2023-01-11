all: G clean
G: main Map Game Figure
	g++ -o ConsoleTetris.exe *.o
main:
	g++ -c -std=c++11 main.cpp -o main.o
Game:
	g++ -c -std=c++11 Game.cpp -o Game.o
Map:
	g++ -c -std=c++11 Figure.cpp -o Figure.o
Figure:
	g++ -c -std=c++11 Map.cpp -o Map.o
clean:
	del *.o

