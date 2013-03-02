#ifndef LIST
#define LIST

#include <iostream>
#include <stddef.h>
#include "List.h"
using namespace std;

List::List(){
      head = NULL;
      iter = head;
      size = 0;
}

//deallocate a list when we are done with it
List::~List(){
     	 Node* cursor = head;
      	 Node* next = NULL;
	 while( cursor != NULL) {
		 next = cursor -> next;
		 delete cursor;
		 cursor = next;
      }
}

// get a node at nth position
Node* List::get_node(list_position p) const {
   list_position curr = 0; 	
   Node* cursor = head;
   // if list has entries iterate thru nodes target times
       while( curr < p && cursor != NULL) {
	      cursor = cursor -> next;
	      curr++;
	      }
       return cursor;
    }

// get a node and save the location of the previous node
Node* List::get_node(list_position p, Node*& prev) const {
   list_position curr = 0; 	
   Node* cursor = head;
   prev = NULL;
   // if list has entries iterate thru nodes target times
       while( curr < p && cursor != NULL) {
	      prev = cursor;
	      cursor = cursor -> next;
	      curr++;
	      }
       return cursor;
}

Node* List::first(){
	return get_node(0);
}

Node* List::last(){
 	return get_node(size-1);
}
Node* List::iter_reset() {
      iter = head;
      return iter;
}

Node* List::iter_next() {
      iter = iter -> next;
      return iter;
}

// insert a node at nth position in list
void List::insert(list_item n, list_position target, list_error& e){
      Node* prev = NULL;
      Node* next = NULL;
      Node* cursor = NULL; 
      e = 0;
// do our own error checking because it is perfectly valid for
// get_node to return null beyond extremes
      if( target > size || target < 0 ) {
	      	e = OUT_OF_RANGE;
	      	return;
      } else if( target == 0 ){       
		next = head;
		cursor = new Node;
		head = cursor;
      } else {
      		cursor = get_node(target, prev);
      		next = cursor;
      		cursor = new Node;
      }
      cursor -> x = n;
// if there is no next node, cursor->next will still be null which is
// what we wanted anyway		     
      cursor -> next = next;
      size++;
// make prev node's next point to new node
      if(prev != NULL) 
	      prev -> next = cursor;
}	

void List::sort(){
	Node* cursor = NULL;
	Node* prev = NULL;
	Node* next = NULL;
	bool did_swap = true;
	int i = 0;

	//run until everything is in order or threshold hit
	while( (size > 1)  && (i < MAX_LIST_SORT_ITERATIONS) && did_swap){
	     did_swap = false;
	     // a special case occurs at head: if we need to swap head and 
	     // second node, head needs to point to the new node.
	     // there's got to be a smarter way to do this, but this should
	     // work
	     prev = head;
	     cursor = head -> next;
	     next = cursor -> next; // define here for slightly more sanity.
	     if( head -> x > cursor -> x){
		     head = cursor;
		     head -> next = prev;
		     prev -> next = next;
		     did_swap = true;
	     }
	     // reset cursor so we know we know once we enter loop we are
	     // starting at node 1 
	     prev = head;
	     while( cursor -> next != NULL){
	     	     next = cursor -> next;
	     // swap places if cursor value greater than next
		     if( cursor -> x > next -> x){
			     prev -> next = next;
			     cursor -> next = next -> next;
			     next -> next = cursor;
			     did_swap = true;
			     prev = next;
		     } else {
		     	     prev = cursor;
		     }
		     cursor = prev-> next;
	     }
	     i++;
	}
	if( i == MAX_LIST_SORT_ITERATIONS-1 ){
	 	cout << "WARNING: Sort operation quit after " << i <<
		 "iterations. List may not be completely in order." <<
		 endl;
	}
}

// convenience function to insert at head	
void List::prepend(list_item n, list_error& e){
      insert(n, 0, e);
}
// convenience function to insert at end of the list	
void List::append(list_item n, list_error& e){
      insert(n, size, e);
}
void List::remove( list_position target, list_error& e){
	Node* prev = NULL;
 	Node* cursor = get_node( target, prev );
	if( cursor == NULL ){
	 	e = OUT_OF_RANGE;
	} else if ( target == 0){
		head = cursor -> next;
		delete cursor;
		size--;
	} else {
		prev -> next = cursor -> next;
		delete cursor;
		size--;
	}
}
list_item List::get_value( list_position p, list_error& e) const{
	Node* cursor = get_node( p );
	if( cursor == NULL ){
		e = OUT_OF_RANGE;
// not really a good way to deal with this as -1 is a realistic int value
// probably should throw an exception instead?
		return -1; 
	} else {
		return cursor -> x;
	}
}
void List::set_value( list_item n, list_position p, list_error& e){
	Node* cursor = get_node( p );
	if( cursor == NULL ){
	 	e = OUT_OF_RANGE;
	} else {
		cursor -> x = n;
	}
}

void List::print() const {
      Node* cursor = head;
      while( cursor != NULL ){
	      cout << cursor -> x << " ";
	      cursor = cursor -> next;
      }
      cout << endl;
}

list_size List::get_size() const {
      return size;
}

#endif
