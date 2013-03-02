#include <cstdio>
#include <fstream>
using namespace std;

#include "Bitstream.h"


int main(int argc, char *argv[]) {
	Bitstream *bs = new Bitstream();	
	ofstream o;
	bs -> write_byte('\n', o);

	return 0;
}
