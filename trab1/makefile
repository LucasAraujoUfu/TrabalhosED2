all:
	make Obj
	mkdir -p bin
	g++ -o bin/main obj/sort.o obj/main.o

Obj: 
	make sort
	make main

main:
	mkdir -p obj
	g++ -c main.cpp -o obj/main.o

sort:
	mkdir -p obj
	g++ -c lib/sort.cpp -o obj/sort.o

clean:
	rm obj/* bin/*
