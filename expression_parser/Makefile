eval: eval.o operator.o Stack.o debug.o
	g++ -o eval eval.o operator.o Stack.o debug.o
eval.o: eval.cpp operator.h Stack.h debug.h
	g++ -c eval.cpp
op-test: op-test.o operator.o debug.o
	g++ -o op-test op-test.o operator.o debug.o
op-test.o: operator.cpp operator.h debug.o
	g++ -c op-test.cpp
operator.o: operator.h operator.cpp
	g++ -c operator.cpp
Stack.o: Stack.h Stack.cpp
	g++ -c Stack.cpp
debug.o: debug.h debug.cpp
	g++ -c debug.cpp
clean:
	rm *.o eval
