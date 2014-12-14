#ifndef _H_FWD_ROAD
#define _H_FWD_ROAD

#include "pointer.h"

class Road;
class RoadClass;

extern void destroy(Road* value);
extern void destroy(RoadClass* value);

using RoadPtr = TPtr < Road > ;
using RoadClassPtr = TPtr < RoadClass > ;

#endif	//	_H_FWD_ROAD