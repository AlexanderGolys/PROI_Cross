all: main.o cross.o 
	g++ main.o cross.o -o prog

main.o: main.cpp
	g++ -c main.cpp

calc.o: cross.cpp
	g++ -c calc.cpp

clean:
	rm -rf *o prog