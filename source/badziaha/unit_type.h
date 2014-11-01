#ifndef _H_UNIT_TYPE
#define _H_UNIT_TYPE

enum class UnitType {
	UnitType1,
	UnitType2
};

class Unit;

extern Unit* GetEtalonUnit(UnitType type);

#endif	//	_H_UNIT_TYPE