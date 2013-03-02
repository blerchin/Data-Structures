#ifndef STACK_H
#define STACK_H
#include <cstddef> // provides NULL
// set the data type of the list elements here
typedef double list_item;
class Node {

  public:
    // set link to NULL
    Node();
    // data to arg 1, set link to arg 2
    Node(const list_item&, Node*);
    // get/set link
    Node*& Link();
    // get/set data
    list_item& Data();

  private:
    list_item data;
    Node* link;
};

class Stack {
  public:
    // default constructor
    Stack();
    // copy constructor
    Stack(const Stack&);
    // destructor
    ~Stack();
    // assignment operator overload
    Stack& operator=(const Stack&);
    // return true if empty, false otherwise
    bool empty() const;
    // return size (number of elements in stack)
    unsigned int size() const;
    // returns a reference to the top element on the stack, leaves it on
    // stack
    list_item& top() const;
    // adds an element to the stack
    void push(const list_item&);
    // removes the top element from the stack
    void pop();

  private:
    Node *head;
    unsigned int num_elements;
};
#endif
