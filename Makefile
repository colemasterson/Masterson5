output: main.o LinkLoader.o Record.o
	g++ -o output main.o LinkLoader.o Record.o -std=c++11
	
main.o: main.cpp
	g++ -c main.cpp -std=c++11

LinkLoader.o: LinkLoader.h LinkLoader.cpp
	g++ -c LinkLoader.cpp -std=c++11

Record.o: Record.h Record.cpp
	g++ -c Record.cpp -std=c++11
clean:
	rm output main.o LinkLoader.o Record.o