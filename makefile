all: tree

tree: main.o
	g++ main.o -o tree

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -rf *.o tree
