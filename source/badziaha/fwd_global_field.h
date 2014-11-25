#ifndef _H_FWD_GLOBAL_FIELD
#define _H_FWD_GLOBAL_FIELD

#include "pointer.h"

class GlobalField;
class GlobalFieldCell;

void destroy(GlobalField* value);
void destroy(GlobalFieldCell* value);

using GlobalFieldPtr = TPtr < GlobalField > ;
using GlobalFieldCellPtr = TPtr < GlobalFieldCell > ;

#endif	//	_H_FWD_GLOBAL_FIELD