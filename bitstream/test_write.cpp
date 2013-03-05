#include <cstdio>
#include <iostream>
#include <sstream>
using namespace std;

#include "Bitstream.h"

// prints all possible bytes
int main(int argc, char *argv[]) {
	Bitstream *bs = new Bitstream();	
	istringstream is;
	ostringstream os;
	string hold;
	unsigned char byte = 0;
	cout << "writing all possible chars, reading them back and "
						"writing them again."<< endl;
	for(int i=0; i<256; i++){
		cout << "i: " << i <<endl;
	// this works. please don't ask questions.
		os.seekp(0);
		bs -> write_byte((char)i, os);
		cout << "written: " << os.str() << endl;
	// hackity hack hack (or maybe this is how you're supposed to deal with
	// pushing ostrings to istrings, i don't know)
		istringstream is( os.str(), istringstream::in);
		bs -> read_byte(byte, is);
		cout << "read value: " << (int)byte << endl;
		cout << "read binary: ";
		bs -> write_byte(byte, cout);
		cout << endl<< endl;
	}

	return 0;
}
