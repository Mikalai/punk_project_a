#ifndef _H_FWD_ITEMS
#define _H_FWD_ITEMS

#include "pointer.h"

class Ammo;
class Item;
class Clothes;
class Weapon;
class ItemClass;
class ClothesClass;
class AmmoClass;
class WeaponClass;

extern void destroy(ItemClass*);
extern void destroy(ClothesClass*);
extern void destroy(AmmoClass*);
extern void destroy(WeaponClass*);
extern void destroy(Item*);
extern void destroy(Clothes*);
extern void destroy(Ammo*);
extern void destroy(Weapon*);

template<class T, void(*D)(T*)> 
struct DestroyPolicy {
	static void destroy(T* value) {
		D(value);
	}
};

template<class T>
using TItemPtr = TPtr < T > ;

using ItemClassPtr = TItemPtr < ItemClass> ;
using ClothesClassPtr = TItemPtr < ClothesClass> ;
using AmmoClassPtr = TItemPtr < AmmoClass>;
using WeaponClassPtr = TItemPtr < WeaponClass> ;

using ItemPtr = TItemPtr < Item> ;
using ClothesPtr = TItemPtr < Clothes> ;
using AmmoPtr = TItemPtr < Ammo>;
using WeaponPtr = TItemPtr < Weapon> ;

#endif	//	_H_FWD_ITEMS