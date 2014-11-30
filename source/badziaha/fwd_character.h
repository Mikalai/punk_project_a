#ifndef _H_FWD_CHARACTER
#define _H_FWD_CHARACTER

#include "pointer.h"

class Character;

void destroy(Character* value);

using CharacterPtr = TPtr < Character > ;

#endif	//	_H_FWD_CHARACTER