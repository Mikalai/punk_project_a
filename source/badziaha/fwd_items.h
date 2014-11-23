#ifndef _H_FWD_ITEMS
#define _H_FWD_ITEMS

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
//
//template<>
//struct DestroyPolicy < ItemClass > {
//	static void destroy(ItemClass* value) {
//		destroy_item_class(value);
//	}
//};
//
//template<>
//struct DestroyPolicy < ClothesClass > {
//	static void destroy(ClothesClass* value) {
//		destroy_clothes_class(value);
//	}
//};
//
//template<>
//struct DestroyPolicy < AmmoClass > {
//	static void destroy(AmmoClass* value) {
//		destroy_ammo_class(value);
//	}
//};
//
//template<>
//struct DestroyPolicy < WeaponClass > {
//	static void destroy(WeaponClass* value) {
//		destroy_weapon_class(value);
//	}
//};
//
//template<>
//struct DestroyPolicy < Clothes > {
//	static void destroy(Clothes* value) {
//		destroy_clothes(value);
//	}
//};
//
//template<>
//struct DestroyPolicy < Item > {
//	static void destroy(Item* value) {
//		destroy_item(value);
//	}
//};
//
//template<>
//struct DestroyPolicy < Ammo > {
//	static void destroy(Ammo* value) {
//		destroy_ammo(value);
//	}
//};
//
//template<>
//struct DestroyPolicy < Weapon > {
//	static void destroy(* value) {
//		destroy_ammo(value);
//	}
//};

template<class T>
using TItemPtr = std::unique_ptr < T, void(*)(T*) > ;

using ItemClassPtr = TItemPtr < ItemClass> ;
using ClothesClassPtr = TItemPtr < ClothesClass> ;
using AmmoClassPtr = TItemPtr < AmmoClass>;
using WeaponClassPtr = TItemPtr < WeaponClass> ;

using ItemPtr = TItemPtr < Item> ;
using ClothesPtr = TItemPtr < Clothes> ;
using AmmoPtr = TItemPtr < Ammo>;
using WeaponPtr = TItemPtr < Weapon> ;

template<class T>
inline TItemPtr<T> make_ptr(T* value) {
	return TItemPtr < T > { value, destroy };
}

template<class T, class U>
inline TItemPtr<T> cast(TItemPtr<U>& v) {
	return make_ptr<T>(static_cast<T*>(v.release()));
}

#endif	//	_H_FWD_ITEMS