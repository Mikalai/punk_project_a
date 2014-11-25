#ifndef _H_FWD_LOCAL_FIELD
#define _H_FWD_LOCAL_FIELD

#include "pointer.h"

class LocalField;
class LocalFieldCell;

extern void destroy(LocalField* value);
extern void destroy(LocalFieldCell* value);

using LocalFieldPtr = TPtr < LocalField > ;
using LocalFieldCellPtr = TPtr < LocalFieldCell > ;

#endif