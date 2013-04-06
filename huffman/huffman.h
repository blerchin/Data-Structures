#include <fstream>
#include <iostream>
#include "bitstream/Bitstream.h"
#define EOF_ORD 256
#define EOL -1

//////////////////////////////////////////////////////////////////////
//HUFFNODE CLASS DEFINITION///////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

class huffnode {
	friend class huffman;
	public:
	int lchild, rchild, parent, weight, nextroot;
	huffnode() {
		lchild = EOL;
		rchild = EOL;
		parent = EOL;
		weight = 0;
		nextroot = EOL;
	};  //huffnode constructor.
};

///////////////////////////////////////////////////////////////////////
//HUFFMAN CLASS HEADER/////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////

class huffman {
	//private: //makes writing tests so much easier
	public:
		int root,		// index of the final root node
				rootlist, 	// pointer to linked list of root nodes
				leaves,		// the number of leaves
				low_node, // = 0,
				high_node; // = 0;
		huffnode node_array[513];		// Huffman tree info.
		Bitstream bitstream;			// bitstream for bit i/o
		ifstream file_in;
		ofstream file_out; 	// i/o filenames


			/////////////////////////////////////////////////////////////////
			// insert.  Given a node position in
			// arg1, insert the node in the list
			// in the right place assuming ascending
			// order.
			void insert(int i); // end insert method (private)

			/////////////////////////////////////////////////////////////////
			// huffman constructor.
			huffman(const char*, const char*);

			/////////////////////////////////////////////////////////////////
			// frequency count of different bytes
			// in the input file.
			void count();

			/////////////////////////////////////////////////////////////////
			// buildtree.  Construct code tree
			// using the Huffman algorithm.
			void buildtree();

			/////////////////////////////////////////////////////////////////
			//putcode.  Put code for character
			//number c into compressed file.
			void putcode(int c);

			/////////////////////////////////////////////////////////////////
			//header.  Put huffman tree into
			//compressed file.
			void putheader();

			/////////////////////////////////////////////////////////////////
			//getheader. gets header
			//information from huffman
			//compressed file and
			//constructs huffman tree in
			//node_array.
			void getheader();

			////////////////////////////////////////////////////////////////
			//encode. Encode the file
			//using the Huffman tree and
			//write it to the
			//compressed file.
			void encode(); 

			////////////////////////////////////////////////////////////////
			//decode. Decode the file
			//using the reconstructed
			//Huffman tree and write
			//it to the decompressed
			//file.
			void decode(); 

			void close();

};
