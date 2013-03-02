#include "debug.h"


void DBG( const char* msg, int lvl ){
	if( lvl <= DEBUG_LVL )
	 	cout << msg << endl;
}
