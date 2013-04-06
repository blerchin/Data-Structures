///////////////////////////////////////////////////////////////////////
// HUFFMAN COMPRESSION CLASS
///////////////////////////////////////////////////////////////////////

#include "huffman.h"

/////////////////////////////////////////////////////////////////
// insert.  Given a node position in
// arg1, insert the node in the list
// in the right place assuming ascending
// order.
void huffman::insert(int i){ 
	int cur = 0;
	// find a node with lower weight to start sort.
	// cout << "Looking for a lower weight node" << endl;
	while( cur < EOF_ORD
				 && node_array[cur].weight >= node_array[i].weight
				 && node_array[cur].weight !=0)
	{
		cur++;
	}
// if we don't find one, make i's nextroot to EOL.
// if we do, follow the next pointers until the next is
// heavier than i, and put i there.
	//cout << "Looking for a place to put node" << endl;
	while(
				node_array[cur].nextroot != EOL
				&& node_array[node_array[cur].nextroot].weight < node_array[i].weight)
	{
		//cout << "cur: " << cur << endl;
		cur = node_array[cur].nextroot;
	} 
	node_array[i].nextroot = node_array[cur].nextroot;
	node_array[cur].nextroot = i;
  if ( -1 == root || node_array[i].weight <= node_array[root].weight) {
	 root = i;
	}
}


/////////////////////////////////////////////////////////////////
// huffman constructor.
huffman::huffman(const char *in, const char *out){

	file_in.open(in);
	file_out.open(out);

	//low_node = 0;
	//high_node = 0;
	root = -1;

	for(int i=0; i<513; i++){
		node_array[i] = huffnode();
	}
	node_array[EOF_ORD].weight = 1;
	
}

/////////////////////////////////////////////////////////////////
// frequency count of different bytes
// in the input file.
void huffman::count(){
	unsigned char c;

	while(!file_in.eof()){
		//cout << "counted char " << (int)c << ": " << node_array[(int)c].weight <<  endl;
		node_array[(int)c].weight++;
		c = (unsigned char) file_in.get() + 126 ;
	}
	int i;
	for(i=0; i<=EOF_ORD; i++){
			//cout << "inserting huffnode " << i << endl;
			if(node_array[i].weight > 0)
				insert(i);
	}
	//cout << "finished counting" << endl;
}

/////////////////////////////////////////////////////////////////
// buildtree.  Construct code tree
// using the Huffman algorithm.
void huffman::buildtree(){
	int i, prev;
	i = EOF_ORD+1;
	prev = root;
	root = node_array[root].nextroot;

	while( 1 ){
		node_array[i].lchild = prev;
		node_array[prev].parent = i;

		node_array[i].rchild = root;
		node_array[root].parent = i;

		node_array[i].weight = node_array[node_array[i].lchild].weight
				+ node_array[node_array[i].rchild].weight;


		prev = i;
		if( node_array[root].nextroot != EOL){
	 		root = node_array[root].nextroot;
			i++;
		}
		else{ 
			root = i;
			break;
		}
	}
	
}

/////////////////////////////////////////////////////////////////
//putcode.  Put code for character
//number c into compressed file.
void huffman::putcode(int c){
	//cout << "putting code for " << c << endl;
	int cur = c;
	bool right = 0;
	if(node_array[node_array[cur].parent].rchild == c)
		right = 1;


	while(1){
		cur = node_array[cur].parent;
		if(node_array[cur].parent == EOL)
			break;
		bitstream.putbit(0, file_out);
	}
	bitstream.putbit(right, file_out);

}

/////////////////////////////////////////////////////////////////
//header.  Put huffman tree into
//compressed file.
void huffman::putheader() {
	bitstream.putint(root, 10, file_out);
	int i;
	for(i=EOF_ORD+1; i <= root; i++){
		bitstream.putint(node_array[i].lchild, 9, file_out);
		bitstream.putint(node_array[i].rchild, 9, file_out);
	}
}

/////////////////////////////////////////////////////////////////
//getheader. gets header
//information from huffman
//compressed file and
//constructs huffman tree in
//node_array.
void huffman::getheader(){
	//cout << "Re-creating tree" << endl << "=======================" << endl;
	bitstream.getint(root, 10, file_in); 
	//cout << "root is " << root << endl;
	int i;
	for(i=EOF_ORD+1; i <= root; i++){
		bitstream.getint(node_array[i].lchild, 9, file_in);
		bitstream.getint(node_array[i].rchild, 9, file_in);
		//cout << "Re-created Huffnode " << i << " with lchild "
		//		<< node_array[i].lchild << " and rchild " << node_array[i].rchild <<
		//		endl;
	}

}

////////////////////////////////////////////////////////////////
//encode. Encode the file
//using the Huffman tree and
//write it to the
//compressed file.
void huffman::encode(){
	file_in.clear();
	file_in.seekg(0);
	unsigned char c;
	while(1){
		c = file_in.get();
		//cout << "about to put code for " << c << endl;
		if(!file_in.eof())
			putcode((int)c + 126);
		else
			break;
	}
	putcode(EOF_ORD);
	bitstream.flush(file_out);
	close();
}

////////////////////////////////////////////////////////////////
//decode. Decode the file
//using the reconstructed
//Huffman tree and write
//it to the decompressed
//file.
void huffman::decode(){
	int cur;
	int b;
	while(1){
		cur = root;
		while(EOL != node_array[cur].rchild){
			bitstream.getbit(b, file_in);
			if(!b){
				cur = node_array[cur].lchild;
			}
			else{
				cur = node_array[cur].rchild;
			}
		}

		if(	EOF_ORD != cur ){
			file_out << (char)(cur - 126);
			//cout << "decoded char " << (int)(cur-127) << endl;
			
		}else{
			//cout << "finished decoding" << endl;
			break;
		}
	} 
	

}

void huffman::close(){
	file_out.close();
	file_in.close();

}
