#include <iostream>
#include "huffman.h"

using namespace std;

const char *test_source = "test_source.dat";
const char *test_compressed = "test_compressed.dat";
const char *test_decompressed = "test_decompressed.dat";

int main(int argc, char* argv[]){
	cout << "starting insertion test:" << endl <<
		"=============================" << endl;
	huffman *h = new huffman(test_source, test_compressed);
	huffman *h2 = new huffman(test_compressed, test_decompressed);
	int i; 
	h->count();
	cout << "Byte Value: Count, Next (Nonzero weight only)" << endl <<
		"=============================" << endl;
	i = h->root;
	while( i != EOL) {
		cout << "Huffnode " << i << ": Weight: " << h->node_array[i].weight << 
				 ", Next: " << h->node_array[i].nextroot << ", L-child: " << h->node_array[i].lchild << ", R-child: " <<
					 h->node_array[i].rchild << ", Parent: " << h->node_array[i].parent <<
					 endl;
		i = h->node_array[i].nextroot;
	} 	
	h->buildtree();
	cout << "Interior Nodes:"<<endl<< "=============================" <<
		endl;
	i = EOF_ORD+1;
	while( i <= h->root) {
		cout << "Huffnode " << i << ": Weight: " << h->node_array[i].weight << 
				 ", Next: " << h->node_array[i].nextroot << ", L-child: " << h->node_array[i].lchild << ", R-child: " <<
					 h->node_array[i].rchild << ", Parent: " << h->node_array[i].parent <<
					 endl;
		i++;
	} 	
	cout << "Root node is " << h->root << endl;
	h->putheader();
	h->encode();
	h->close();
	h2->getheader();
	h2->decode();
	h2->close();
	
}

