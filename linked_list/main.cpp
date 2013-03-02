#include <iostream>
#include <fstream>
#include <math.h>
#include "List.h"
#include <stddef.h>
#include <string.h>

using namespace std;

list_item list_mean( List& l ){
 	long sum = 0;
	list_item val = 0;
	Node* cursor = l.iter_reset();
 	while( cursor != NULL ){
	 	val = cursor -> x;
		sum += val;
		cursor = l.iter_next();
	}
	return sum / l.get_size();
}
list_item list_median( List& l){
	list_size size = l.get_size();
	list_error e = 0;

	if( size % 2 ){
		return l.get_value( size/2, e);
	} else {
	 	list_position p = floor(size/2);
		return ( l.get_value( p, e ) + l.get_value( p+1, e ) ) / 2;
	}
}

list_item list_stdev( List& l){
	list_item mean = list_mean( l );
	list_item dev = 0;
	long sum_devs = 0;
	Node* cursor = l.iter_reset();
	while( cursor != NULL ){
		dev = mean - cursor -> x;
	 	sum_devs += dev*dev;	
		cursor = l.iter_next();
	}
	return sqrt( sum_devs / l.get_size() );
}

void print_stats( List& l, list_error& e) {
	l.print();
	cout << "size: " << l.get_size() << endl;
	cout << "mean: " << list_mean( l ) << endl;
	cout << "median: " << list_median( l ) << endl;
	cout << "stdev: " << list_stdev( l ) << endl;
	if( e != 0)
	 	cout << "error: " << e << endl;
}

int main(int argc, char *argv[]){
	List l;
	list_error e;
	double x;

	ifstream NUMBERS(argv[1]);
	if(!NUMBERS){
		cout<< "File not found!"<<endl;
	}else{
	       while( NUMBERS>>x){
		       l.prepend(x,e);
	       }
	       NUMBERS.close();
	       l.sort();
	       print_stats(l,e);
	}
	cout << endl << "Enter a number or a series of space-delimited numbers to add to the list:" << endl;
	while( cin.peek() != '\n' && cin >> x ){
		//remove trailing newline so while loop doesn't
		//automatically evaluate as false. probably only works on
		//unix, but whatever.
		cin.ignore(1,'\n');
		l.prepend(x, e);
		l.sort();
		print_stats(l,e);	
	}
	return 0;

}
