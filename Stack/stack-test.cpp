#include <iostream>
#include <fstream>
#include "Stack.h"

using namespace std;

void pbv(Stack);

int main(int argc, char *argv[]) {
  Stack s;

  // Pass by reference copy constructor
  cout << "**************************************************" << endl;
  cout << "** Pass by value test **" << endl;
  s.push(1);
  pbv(s);
  cout << "Pass by value:" << s.top() << endl;;
  cout << "    Should be:" << 1 << endl;;
  // Empty() test
  cout << "**************************************************" << endl;
  cout << "** empty() **" << endl;
  cout << "      empty(): " << s.empty() << endl;
  cout << "    Should be: " << false << endl;
  s.pop();
  cout << "      empty(): " << s.empty() << endl;
  cout << "    Should be: " << true << endl;
  // size() test
  cout << "**************************************************" << endl;
  s.push(1); s.push(2);
  cout << "** size() **" << endl;
  cout << "       size(): " << s.size() << endl;
  cout << "    Should be: " << 2 << endl;

  cout << "**************************************************" << endl;
  cout << "** top() **" << endl;
  cout << "        top(): " << s.top() << endl;
  cout << "    Should be: " << 2 << endl;

  cout << "**************************************************" << endl;
  cout << "** pop() **" << endl;
  s.pop();
  cout << "size() after pop(): " << s.size() << endl;
  cout << "         Should be: " << 1 << endl;
  s.pop();
  cout << "size() after pop(): " << s.size() << endl;
  cout << "         Should be: " << 0 << endl;

  cout << "**************************************************" << endl;
  cout << "** operator=() **" << endl;

  cout << "Simple assignment.\n";
  s.push(1); s.push(2);
  Stack t;
  t = s;
  t.push(3);
  cout << "After t=s:\n";
  cout << "         s: ";
  while(!s.empty()) {
    cout << s.top() << " ";
    s.pop();
  }
  cout << endl;
  cout << " Should be: 2 1" << endl;
  cout << "         t: ";
  while(!t.empty()) {
    cout << t.top() << " ";
    t.pop();
  }
  cout << endl;
  cout << " Should be: 3 2 1" << endl;

  cout << "Self assignment.\n";
  s.push(1); s.push(2);
  s=s;
  cout << "After s=s:\n";
  cout << "         s: ";
  while(!s.empty()) {
    cout << s.top() << " ";
    s.pop();
  }
  cout << endl;
  cout << " Should be: 2 1" << endl;

  cout << "Assignment to pre-existing stack.\n";
  s.push(1); s.push(2);
  t.push(3); t.push(4);
  t=s;
  cout << "         t: ";
  while(!s.empty()) {
    cout << s.top() << " ";
    s.pop();
  }
  cout << endl;
  cout << " Should be: 2 1" << endl;

  

  cout << "Recursive assignment.\n";
  s.push(1); s.push(2);
  Stack u;
  u = t = s;
  t.push(3);
  u.push(4);
  cout << "After u=t=s:\n";
  cout << "         s: ";
  while(!s.empty()) {
    cout << s.top() << " ";
    s.pop();
  }
  cout << endl;
  cout << " Should be: 2 1" << endl;
  cout << "         t: ";
  while(!t.empty()) {
    cout << t.top() << " ";
    t.pop();
  }
  cout << endl;
  cout << " Should be: 3 2 1" << endl;
  cout << "         u: ";
  while(!u.empty()) {
    cout << u.top() << " ";
    u.pop();
  }
  cout << endl;
  cout << " Should be: 4 2 1" << endl;


  cout << "**************************************************" << endl;
  cout << "** Copy constructor **" << endl;
  s.push(1); s.push(2);
  t = Stack(s);
  cout << "         t: ";
  while(!t.empty()) {
    cout << t.top() << " ";
    t.pop();
  }
  cout << endl;
  cout << " Should be: 2 1" << endl;

}


void pbv(Stack s) {
  cout << "Pass by value:" << s.top() << endl;;
  cout << "    Should be:" << 1 << endl;;
  s.push(-1);
  cout << "Pass by value:" << s.top() << endl;;
  cout << "    Should be:" << -1 << endl;;
}
