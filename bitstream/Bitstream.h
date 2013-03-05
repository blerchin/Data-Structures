#include <fstream>
#include <iostream>
using namespace std; 

#define DEBUG 1

#define NEWLINE '\n'
// you never know when you're gonna have to chnage these guys...
#define ZERO '0'
#define ONE '1'
#define BYTE_SIZE 8 

class Bitstream { 
	private: 
		unsigned char bytebuffer;
		int obitpos, ibitpos;

	public:
		// Sets bit position to zero.
		Bitstream();  
		// Calls flush
		~Bitstream();
		// write out last bytebuffer. 
		void flush(ofstream &file_out); 
		// Puts binary 0 or 1 into the destination file.
		void putbit (int c, ofstream &file_out);     
		// Gets next bit from the input file, places it in the first argument.
		bool getbit(int &b, ifstream &file_in);  
		// Puts integer n in b-bit representation into file_out
		void putint(int n, int b, ofstream &file_out); 
		// Gets integer n in b-bit representation from
		// file_in
		void getint(int &n, int b, ifstream &file_in);   
		// writes 1 and 0 chars to cout if DEBUG is true,
		// otherwise a byte to file
		void write_byte(const unsigned char byte, ostream &out);
		// reads 8x ascii chars 1 or 0 from cin if DEBUG is true,
		// otherwise reads a byte from file (wrapper for .get() )
		void read_byte(unsigned char &byte, istream &in);
};
