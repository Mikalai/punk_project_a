#ifndef _H_RESOURCES
#define _H_RESOURCES

#include <QtCore/qstring.h>
#include <map>
#include <memory>
#include <vector>
#include "item_class_type.h"
#include "fwd_items.h"
#include "fwd_surface_type.h"


class QImage;
enum class ModelType;

class Resources {
public:

	using ItemClasses = std::vector < const ItemClass* > ;
	using ClothesClasses = std::vector < const ClothesClass* > ;
	using AmmoClasses = std::vector < const AmmoClass* > ;
	using WeaponClasses = std::vector < const WeaponClass* > ;
	using WeaponClipClasses = std::vector < const WeaponClipClass* >;
	using SurfaceTypeClasses = std::vector < const SurfaceTypeClass* > ;
	Resources();

	static void destroy();
	static const SurfaceTypeClasses& surface_types() { return instance()->_surface_types(); }

	static const ItemClasses& items() { return instance()->_items(); }
	static const ClothesClasses& clothes() { return instance()->_clothes(); }
	static const AmmoClasses& ammos() { return instance()->_ammos(); }
	static const WeaponClasses weapons() { return instance()->_weapons(); }
	static const WeaponClipClasses weapon_clips() { return instance()->_weapon_clips(); }

	QImage* getSquadImage();
	QImage* getCityImage();
	QImage* modelImage(const ModelType& value);	
	QImage* loadImage(const QString& value);

	static Resources* instance();

private:

	const SurfaceTypeClasses& _surface_types() const { return m_surfaces_cache; }

	const ItemClasses& _items() const { return m_items_cache; }
	const ClothesClasses& _clothes() const { return m_clothes_cache; }
	const AmmoClasses& _ammos() const { return m_ammo_cache; }
	const WeaponClasses _weapons() const { return m_weapon_cache; }
	const WeaponClipClasses _weapon_clips() const { return m_weapon_clip_cache; }
private:
	void readItems();

private:
	static std::unique_ptr<Resources> m_instance;
	std::vector<std::unique_ptr<QImage>> m_GLOBAL_FIELD_CELL_REAL_SIZE_ground;
	std::unique_ptr<QImage> m_squad_image;
	std::unique_ptr<QImage> m_city_image;
	std::vector<std::unique_ptr<QImage>> m_models;
	std::map<QString, std::unique_ptr<QImage>> m_images;
	std::vector<ItemClassPtr> m_items;
	std::vector<SurfaceTypeClassPtr> m_surface_types;
	ItemClasses m_items_cache;
	ClothesClasses m_clothes_cache;
	AmmoClasses m_ammo_cache;
	WeaponClasses m_weapon_cache;
	WeaponClipClasses m_weapon_clip_cache;
	SurfaceTypeClasses m_surfaces_cache;
};

#endif	//	_H_RESOURCES