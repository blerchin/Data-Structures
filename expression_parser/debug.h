#ifndef DEBUG_H
#define DEBUG_H 1

#include <iostream>
#include <string>

#define DEBUG_S 0 //silent
#define DEBUG_E 10 //error
#define DEBUG_V 30 //verbose

#define DEBUG_LVL 10

using namespace std;

void DBG(const char*, const char*, int ); 

#endif
