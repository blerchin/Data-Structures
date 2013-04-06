#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"

using namespace std;

#define MODE_HZIP 0
#define MODE_HUNZIP 1


#define HZIP_ERROR 1

bool mode = MODE_HZIP;

int main(int argc, char* argv[]){
	if(NULL != strstr(argv[0], "hunzip"))
		mode = MODE_HUNZIP;

	if(MODE_HUNZIP == mode)
		cout << "UNZIP mode" << endl;
	else
		cout << "ZIP mode" << endl;

	if(argc < 3){
		cout << "Error: not enough arguments." << endl;
		return HZIP_ERROR;
	}
	if(strlen(argv[1]) < 0){
		cout << "Error: source file not given." << endl;
		return HZIP_ERROR;
	}
	if(strlen(argv[2]) < 0){
		cout << "Error: destination file not given." << endl;
		return HZIP_ERROR;
	}

	huffman h(argv[1], argv[2]);

	if(MODE_HZIP == mode){
		cout << "compressing " << argv[1] << " to " << argv[2] << endl
			<<	"=============================" << endl;
		h.count();
		h.buildtree();
		h.putheader();
		h.encode();
		cout << "finished compression to " << argv[2] << endl;

	} else if(MODE_HUNZIP == mode){
		cout << "decompressing " << argv[1] << " to " << argv[2] << endl
			<<	"=============================" << endl;
		h.getheader();
		h.decode();
		cout << "finished decompressing to " << argv[2]<< endl;
	}
	h.close();
}

