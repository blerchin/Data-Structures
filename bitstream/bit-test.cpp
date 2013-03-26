#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
using namespace std;

#include "Bitstream.h"


#define OPT_NONE 0
#define OPT_IN_NAME 1
#define OPT_OUT_NAME 2
#define OPT_BIT_REP 3
#define OPT_LIST_CONTENTS 4
#define OPT_WRITE_INTS 5

const char *menu_prompt =
							"Bitstream Test Options: \n" 
							"======================  \n" 
							"1. set the name of the input file \n" 
							"2. set the name of the output file \n" 
							"3. set the number of bits in the bit representation \n" 
							"4. list the contents of the input file as integers \n" 
							"5. write integers to the output file in b-bit" 
							"representation \n" 
							"====================== \n" 
							"Please enter the appropriate option: \n";


string file_in;
string file_out;
int bit_rep = 0;
ifstream *in = new ifstream;
ofstream *out = new ofstream;

int main(int argc, char *argv[]){
	int menu();

	while( menu( ) );

}

int menu( ){
	int ret_val = 1;
	cout << menu_prompt;
	int menu_opt = 0;
	if(cin.peek() == '\n'){
		cin.get();
	}else{
		cin >> menu_opt;
	}

	switch( menu_opt ){
		case OPT_NONE:
			cout << "No option selected. Try again." << endl;
			break;

		case OPT_IN_NAME:
			cout << "Enter input file name:" << endl;
			cin >> file_in;
			cout << "Input file name set to '" << file_in << "'." << endl;
			break;

		case OPT_OUT_NAME:
			cout << "Enter output file name:" << endl;
			cin >> file_out;
			cout << "Output file name set to '" << file_out << "'." << endl;
			break;

		case OPT_BIT_REP:
			{
				cout << "Enter desired bit representation (max 16):";
				cin >> bit_rep;

				if(bit_rep > 16){
					cout << "ERROR: Bit representation too high. Please set to <= 16" 
						<< endl;
					bit_rep = 0;
				} else {
					cout << "Bit representation set to " << bit_rep << "." << endl;
				}
			}
				break;

		case OPT_LIST_CONTENTS:
			{
				if(bit_rep == 0) {
					cout << "Please set bit representation first." << endl;
					break;
				}
				if(file_in.size() == 0){
					cout << "Please set input file first." << endl;
					break;
				}
				cout << "Listing the contents of file '" << file_in 
					<< "' as " << bit_rep << "-bits per integer." << endl;
				cout << "==============================" << endl;
				
				in -> open( file_in.c_str() );
				Bitstream *b = new Bitstream();

				int buf = 0;
				while(1){
						b -> getint(buf, bit_rep, *in);	
						if( in -> eof()) break;
						cout << buf << " ";
				}
				cout << endl;
				in -> close();
			}
				break;	

		case OPT_WRITE_INTS:
			{
				if(bit_rep == 0) {
					cout << "Please set bit representation first." << endl;
					break;
				}
				if(file_out.size() == 0){
					cout << "Please set output file first." << endl;
					break;
				}
				cout << "Write integers to file '" << file_out
					<< "' one at a time:" << endl;
				cout << "==================================="<<endl;
				int to_write = 0;
				
				out -> open(file_out.c_str());
				cin.ignore();
				Bitstream *b = new Bitstream();
				while(cin.peek()!= '\n' && cin >> to_write){
					b -> putint(to_write, bit_rep, *out);
					cout << "writing " << to_write << " to file." << endl;
					cin.ignore();
				}
				cout << "Closing file." << endl;
				b -> flush(*out);
				out -> close();
				break;
			}

		default:
			ret_val = 0;
			break;
	}
	cin.ignore();
	cin.clear();
}

