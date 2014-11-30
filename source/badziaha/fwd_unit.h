#ifndef _H_FWD_UNIT
#define _H_FWD_UNIT

#include "pointer.h"

class Unit;

void destroy(Unit* value);

using UnitPtr = TPtr < Unit > ;

#endif	// _H_FWD_UNIT