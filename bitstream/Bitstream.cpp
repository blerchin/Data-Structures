#include "Bitstream.h"

// Sets bit position to zero.
Bitstream::Bitstream() {
	obitpos = 0;
	ibitpos = 0;
	mask_zero = 127 <<1;
	mask_one = 1;
	mask_prefix = 1 << 7;
}
Bitstream::~Bitstream() {
}

// writes byte as 1 and 0 chars to ostream if DEBUG is true,
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
	if(DEBUG){
			for(int i=0; i<BYTE_SIZE;	i++){
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
	obitpos = 0;
	write_byte(obytebuffer, file_out);
}
// Puts binary 0 or 1 into the destination file.
void Bitstream::putbit (int c, ofstream &file_out){     
	obytebuffer = obytebuffer << 1;
	if(0 == c){
		obytebuffer = mask_zero & obytebuffer;
	} else {
		obytebuffer = mask_one | obytebuffer;
	}
	obitpos++;
	if(BYTE_SIZE == obitpos){
		flush(file_out);
	}
}
// Gets next bit from the input file, places it in the first argument.
bool Bitstream::getbit(int &b, ifstream &file_in){
		if(0 == ibitpos){
			read_byte(ibytebuffer, file_in);
			ibitpos = 1;
		}	else if ((BYTE_SIZE-1) == ibitpos){
			ibitpos = 0;
			ibytebuffer = ibytebuffer << 1;
		} else {
			ibitpos++;
			ibytebuffer = ibytebuffer << 1;
		}
	if(!file_in.eof() ) {
		if(mask_prefix == (ibytebuffer & mask_prefix) ) {
			b = 1;
		}else{
			b = 0;
		}
		return true;

	} else {
		return false;
	}
}
// Puts integer n in b-bit representation into file_out
void Bitstream::putint(int n, int b, ofstream &file_out){
	for(int i=0; i<b; i++) {
		int mask = mask_one << (b-1);
		int bit = (mask  == ((unsigned int) n & mask ));
		putbit(bit , file_out);
		n = n << 1;
	}
}
// Gets integer n in b-bit representation from
// file_in
void Bitstream::getint(int &n, int b, ifstream &file_in){
	int bit = 0;
	n = 0;
	for(int i=0; i<b; i++){
		getbit(bit,file_in);
		if(0 < bit)	n = n | mask_one;
		if((b-1)>i) n = n << 1;
	}
}
