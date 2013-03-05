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
void Bitstream::write_byte(const unsigned char byte, ostream &out){
	if(DEBUG){
		unsigned char b = byte;
		unsigned char mask = 1 << 7;
		for(char i=0; i<BYTE_SIZE; i++){
			if((b & mask) == mask){
				out.put(ONE);
			}else{
				out.put(ZERO);
			}
			//if(i < (BYTE_SIZE-1) ) 
				b = b << 1;
		}
	} else {
		out.put(byte);
	}
}

// reads 8x ascii chars 1 or 0 from cin if DEBUG is true,
// otherwise reads a byte from file (wrapper for .get() )
void Bitstream::read_byte(unsigned char& byte, istream &in){
	unsigned char bit = 0;
	byte = 0;
	unsigned char mask_zero = 127 << 1;
	if(DEBUG){
			for(int i; i<BYTE_SIZE;	i++){
				char to_parse = in.get();
				if( to_parse == ZERO ){
					byte = mask_zero & byte;
				} else {
					byte = 1 | byte;
				}
				if(i<7)	byte = byte << 1;
			}
	} else {
		byte = in.get();
	}

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
