#include "debug.h"


void DBG( const char* id, const char* msg, int lvl ){
	if( lvl <= DEBUG_LVL )
	 	cout << id << ": " << msg << endl;
}
