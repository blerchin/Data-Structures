#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <cstddef> // provides NULL

// define error conditions
#define OUT_OF_RANGE 1

// define behavior conditions
#define MAX_LIST_SORT_ITERATIONS 300

// set the data type of the list elements here
typedef double list_item;
typedef int list_position;
typedef int list_error;
typedef int list_size;

struct Node {
    list_item x;
    Node* next;
};

class List {
  public:
    // construct an empty list
    List(); 
    // delete all nodes
    ~List(); 
    // return pointer to first element
    Node* first(); 
    // return to last element
    Node* last(); 
    // return pointer to pth element in list, NULL if not possible  (use
    // this to modify a node)
    Node* get_node(list_position p) const; 
    // same idea, but this time save a reference to prev node
    Node* get_node(list_position p, Node*& prev) const; 
    // a basic iterator for the list. iter_reset() returns head.
    // iter_next() returns the next node, starting at position 1
    // and advances one position each time it is called.
    Node* iter_reset();
    Node* iter_next();
    // insert item n at position target (allocate a node), existing nodes
    // at position target and after all increase their positions by 1,
    // return e=1 if target is out of range
    void insert(list_item n, list_position target, list_error& e);
    void prepend(list_item n, list_error& e);
    void append(list_item n, list_error& e);
    // remove element at target position (deallocate a node), nodes after
    // position target all decrease their positions by 1, return e=1 if
    // target is out of range
    void remove(list_position target, list_error& e);
    // return value of pth element, return e=1 if no such element
    list_item get_value(list_position p, list_error& e) const;
    // set value of pth element, return e=1 if no such element
    void set_value(list_item n, list_position p, list_error& e);
    // sort the values in the list in ascending order
    void sort();
    // print the values in the list from 1st to last
    void print() const;
    list_size get_size() const;

  private:
   Node* head;
   list_size size; 
   Node* iter;
};
#endif
