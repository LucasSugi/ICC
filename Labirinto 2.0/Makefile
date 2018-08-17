#Makefile :: grafo

all: graph.o main.o
	 gcc -o Graph graph.o main.o

graph.o: graph.c
	gcc -c graph.c

main.o: main.c
	gcc -c main.c

run:
	./Graph
