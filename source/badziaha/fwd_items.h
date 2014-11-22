#ifndef _H_FWD_ITEMS
#define _H_FWD_ITEMS

class Item;
class Clothes;
class ItemClass;
class ClothesClass;

extern void destroy_item_class(ItemClass*);
extern void destroy_clothes_class(ClothesClass*);
extern void destroy_item(Item*);
extern void destroy_clothes(Clothes*);

template<class T> struct DestroyPolicy;

template<>
struct DestroyPolicy < ItemClass > {
	static void destroy(ItemClass* value) {
		destroy_item_class(value);
	}
};

template<>
struct DestroyPolicy < ClothesClass > {
	static void destroy(ClothesClass* value) {
		destroy_clothes_class(value);
	}
};

template<>
struct DestroyPolicy < Clothes > {
	static void destroy(Clothes* value) {
		destroy_clothes(value);
	}
};

template<>
struct DestroyPolicy < Item > {
	static void destroy(Item* value) {
		destroy_item(value);
	}
};

template<class T>
using TItemPtr = std::unique_ptr < T, void(*)(T*) > ;

using ItemClassPtr = TItemPtr < ItemClass > ;
using ClothesClassPtr = TItemPtr < ClothesClass > ;
using ItemPtr = TItemPtr < Item > ;
using ClothesPtr = TItemPtr < Clothes > ;

template<class T>
inline TItemPtr<T> make_ptr(T* value) {
	return TItemPtr < T > { value, DestroyPolicy<T>::destroy };
}

template<class T, class U>
inline TItemPtr<T> cast(TItemPtr<U>& v) {
	return make_ptr<T>(static_cast<T*>(v.release()));
}

#endif	//	_H_FWD_ITEMS