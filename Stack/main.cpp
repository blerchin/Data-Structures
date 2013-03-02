#include <iostream>
#include <fstream>
#include <stdlib.h>

#include "debug.h"
#include "Stack.h"
using namespace std;


// passing by value mostly to check copy constructor
void print_stack( Stack s ){
 	while( !s.empty() ){
		cout << s.top() << " ";
		s.pop();
	}
	cout << endl;
}

int main( int argc, char *argv[], char *envp[] ){
 	Stack s;
	int x;

	ifstream NUMBERS(argv[1]);
	if(!NUMBERS){
		cout<< "File not found!"<<endl;
	}else{
	 	DBG("adding numbers to stack", DEBUG_V);
	       	while( NUMBERS>>x){
		       s.push( x );
	       	}
	       	NUMBERS.close();
	}
	print_stack( s );
	
}
