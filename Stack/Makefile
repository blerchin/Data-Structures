reverse: main.o Stack.o debug.o
	g++ -o reverse Stack.o debug.o main.o
main.o: main.cpp Stack.h debug.o	
	g++ -c main.cpp
Stack.o: Stack.h Stack.cpp
	g++ -c Stack.cpp
debug.o: debug.h debug.cpp
	g++ -c debug.cpp
clean:
	rm *.o reverse
