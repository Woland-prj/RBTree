all: tree

debug: debug.o
	g++ main.o -g -o tree

tree: main.o
	g++ main.o -o tree

main.o: 
	g++ -c main.cpp

debug.o: 
	g++ -c -g main.cpp

clean:
	rm -rf *.o tree

# CC=g++
# CFLAGS=-c -g -Wall
# LDFLAGS=
# SOURCES=main.cpp
# OBJECTS=$(SOURCES:.cpp=.o)
# EXECUTABLE=tree

# all: $(SOURCES) $(EXECUTABLE)
	
# $(EXECUTABLE): $(OBJECTS) 
# 	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

# .cpp.o:
# 	$(CC) $(CFLAGS) $< -o $@