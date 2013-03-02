stats: main.o List.o
	g++ -o stats main.o List.o
main.o: main.cpp List.h	
	g++ -c main.cpp
List.o: List.h List.cpp
	g++ -c List.cpp
clean:
	rm *.o stats
