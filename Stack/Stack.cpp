#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <cassert>
using namespace std;

#include "Stack.h"
#include "debug.h"

// Node member functions
Node::Node(){
	link = NULL;

}
Node::Node( const list_item& new_data, Node* new_link){
	data = new_data;
	link = new_link;
}
Node*& Node::Link(){	
 	return link;
}
list_item& Node::Data(){
	return data;
}


// initialize the stack. do not assign HEAD at this time. we will add upon
// first push.
Stack::Stack(){
	head = NULL; 
	num_elements = 0;
}

Stack::~Stack(){
	Node* cursor = head;
	Node* prev = NULL;
	while( cursor != NULL ){
		prev = cursor;
		cursor = cursor -> Link();
		delete prev;
	}
}

Stack::Stack( const Stack& source ){
	head = NULL;
 	(*this) = source;
}

Stack& Stack::operator=( const Stack& rhs ){
 	DBG( "using assignment op", DEBUG_V);
	if( &rhs != this ){
		Node* cursor = head;
		Node* prev = NULL;
		while( cursor != NULL ){
			prev = cursor;
			cursor = cursor -> Link();
			delete prev;
		}
		DBG( "old nodes deleted", DEBUG_V);
		num_elements = rhs.num_elements;
		head = new Node( rhs.head -> Data(), NULL);
		Node* rhs_cursor = rhs.head -> Link();
		prev = head;
		while( rhs_cursor != NULL ){
		 	DBG("copying a node", DEBUG_V);
			cursor = new Node( rhs_cursor -> Data(),
			  NULL );
			prev -> Link() = cursor;
			rhs_cursor = rhs_cursor -> Link();
			prev = cursor;
			DBG("done copying a node", DEBUG_V);
		}
	}
	DBG( "done copying Stack", DEBUG_V);
	return (*this);		
}

bool Stack::empty() const {
	return num_elements == 0;
}

unsigned int Stack::size() const{
	return num_elements;
}

list_item& Stack::top() const{
 	assert(!empty());
	return head -> Data();
}

void Stack::push( const list_item& new_data ) {
 	Node* next;	
 	if( NULL == head )
	 	next = NULL;
	else
	 	next = head;

	Node* new_node = new Node( new_data, next );
	head = new_node;
	num_elements++;
	DBG("Pushed a node to stack", DEBUG_V );
}

void Stack::pop(){
	Node* temp = head;
	head = head -> Link();
	delete temp;
	num_elements--;
}


