#include "Bitstream.h"

// Sets bit position to zero.
Bitstream::Bitstream() {
	obitpos = 0;
	ibitpos = 0;
}
Bitstream::~Bitstream() {
}

// writes byte as 1 and 0 chars to cout if DEBUG is true,
// otherwise a byte to file
void Bitstream::write_byte(const unsigned char byte, ofstream &file_out){
	if(DEBUG){
		unsigned char b = byte;
		unsigned char mask = 1 << 6;
		for(char i=0; i<7; i++){
			cout << ((b & mask) == mask);
			b = b << 1;
		}
		cout << NEWLINE;
	} else {
		file_out.put(byte);
	}
}

// reads 8x ascii chars 1 or 0 from cin if DEBUG is true,
// otherwise reads a byte from file (wrapper for .get() )
void Bitstream::read_byte(char byte, ifstream &file_in){
}

// write out last bytebuffer. 
void Bitstream::flush(ofstream &file_out){

}
// Puts binary 0 or 1 into the destination file.
void Bitstream::putbit (int c, ofstream &file_out){     
}
// Gets next bit from the input file, places it in the first argument.
bool Bitstream::getbit(int &b, ifstream &file_in){
}
// Puts integer n in b-bit representation into file_out
void Bitstream::putint(int n, int b, ofstream &file_out){
}
// Gets integer n in b-bit representation from
// file_in
void Bitstream::getint(int &n, int b, ifstream &file_in){
}
