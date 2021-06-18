all:
	make Obj
	make Bin

main:
	mkdir -p obj
	g++ -c main.cpp -o obj/main.o

graph:
	mkdir -p obj
	g++ -c lib/graph.cpp -o obj/graph.o

Obj:
	make graph
	make main
	
Bin:
	mkdir -p bin
	g++ obj/graph.o obj/main.o -o bin/prog

clean:
	rm obj/graph.o obj/main.o
	rm bin/prog

