#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <boost/thread/thread.hpp>

void par_merge(int *values, long size, int height);
void merge( int *lhs, int *rhs, long size);
void bubblesort(int *A, int n);
void swap( int *A, int i, int j);
void quicksort( int *A, int i, int j);

struct timeval tim;

boost::mutex io_mutex;

int main(int argc, char* argv[]){
	if(argc == 3){
		int d;
		long m;
		d = atoi(argv[1]);
		m = atol(argv[2]);
		std::cerr << "Number of processors: 2^" << d << " Problem Size: 8*" << m 
			<<	std::endl;
		//dynamically allocating to increase max size
		int *values = new int[8*m];
		long i;
		srand(time(NULL));
		std::cerr << "Filling test array at random..." << std::endl;
		for(i=0; i<8*m; i++){
			values[i] = rand() % 1000;
			//values[i] = i / (m/10);
		//	std::cout << values[i] << " ";
		}
		std::cerr << std::endl << "Starting Clock" << std:: endl;
		gettimeofday(&tim, NULL);  
		double t0 = tim.tv_sec+(tim.tv_usec/1000000.0);  

		std::cerr << std::endl << "Sorting..." << std::endl;
		par_merge(values, 8*m, d);
		gettimeofday(&tim, NULL);  
		double t1 = tim.tv_sec+(tim.tv_usec/1000000.0);
		std::cout << t1-t0 << std::endl;

		/*
		std::cerr << "values after merge: " << std::endl;
		for(i=0; i<8*m; i++){
			std::cerr << values[i] << " ";
		}
		std::cerr << std::endl;
		*/


		delete values;


	} else {
		std::cerr << "Sorry, I didn't get the right number of arguments." <<
			argc << std::endl
			<< "Usage: mergesort [d] [m]" << std::endl;

	}
}

void par_merge(int *values, long size, int height) {
	io_mutex.lock();
	std::cerr << "height: " << height << "\tsize: " << size << std::endl;
	io_mutex.unlock();
	if(height > 0){
		int *lhs = values;
		int *rhs = values + (size/2);
		boost::thread t(par_merge, lhs, size/2, height-1);
		par_merge(rhs, size/2, height-1);
		t.join();
		merge(lhs, rhs, size);

	} else {
		quicksort(values, 0, size-1);
		//bubblesort(values, size);
		/*
		io_mutex.lock();
		std::cout << "Array slice after sort:" << std::endl;
		long i;
		for(i=0; i<size; i++){
			std::cout << values[i];
		}
		std::cout << std::endl << std::endl;
		io_mutex.unlock();
		*/
	}

}
// accept pointers to lhs of array and rhs. Merge sorts and replaces
// array values, STARTING AT *lhs
// size is the size of lhs + rhs
//
// N.B.: this only works if *lhs and *rhs point to adjacent parts of
// the same array. Otherwise, all sorts of havoc!!
void merge( int *lhs, int *rhs, long size) {
	int *sorted = new int[size];	
	int s = 0;
	int r = 0;
	int l = 0;

	while( l<(size/2) && r<(size/2) ){
		if(lhs[l] < rhs[r]){
			sorted[s++] = lhs[l++];
		} else {
			sorted[s++] = rhs[r++];
		}
	}
	while(l < (size/2))
		sorted[s++] = lhs[l++];
	while(r < (size/2))
		sorted[s++] = rhs[r++];

	io_mutex.lock();
	io_mutex.unlock();
	memcpy( lhs, sorted, sizeof(int) * size);
	delete sorted;
}



void bubblesort(int *A , int n) {
	int top,pair;
	for (top = n-1; top >= 0; top--) {
		for (pair = 0; pair < top; pair++) {
			if (A[pair] > A[pair+1]){
				swap(A, pair, pair+1);
			}
		}
	}
}
void swap(int *A, int i, int j){
				int tmp;
				tmp = A[i];
				A[i] = A[j];
				A[j] = tmp;
}
void quicksort(int *A, int i, int j)
{
	int l,r,m;
	if (i+1 < j) {
		// There are at least 3 items in this subarray.
		l=i+1; r=j; m=(i+j)/2;
		if (A[i]<A[m]) swap(A, i, m);
		if (A[j]<A[i]) swap(A, j, i);
		if (A[i]<A[m]) swap(A, i, m);
		// The median of A[i], A[m], A[j] is now at position i.
		while (r>l) {
			while ( l <= j && A[l] <= A[i] )
				l++;
			while ( A[r] > A[i] )
				r--;
			if ( l < r ) swap (A, l, r);
		}
		swap(A, i, r);
		quicksort(A,i,r-1);
		quicksort(A,l,j);
	} else
		// If there are two items in the subarray, sort them.
		if (i<j && A[i]>A[j]) swap(A, i, j);
}
