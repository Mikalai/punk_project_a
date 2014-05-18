//#ifndef _H_PUNK_VIRTUAL_MATERIAL_MANAGER
//#define _H_PUNK_VIRTUAL_MATERIAL_MANAGER
//
//#include "../../system/environment.h"
//#include "../data/material.h"
//
////namespace Attributes
////{
////	class Material;
////};
////
////namespace System
////{
////	template<> class PUNK_ENGINE_API Policy<Attributes::Material>
////	{
////	public:
////		static const Core::String GetResourceFile() { return L"resource"; }
////		static const Core::String GetExtension() { return L"*.material"; }
////		static const Core::String GetFolder() { return System::Environment::Instance()->GetTextureFolder(); }	
////		static System::ObjectType GetResourceType() { return System::ObjectType::MATERIAL; }
////		static void OnInit() {}
////		static void OnDestroy() {}
////	};
////}
////
////namespace Attributes
////{
////	class PUNK_ENGINE_API MaterialManager : public System::ResourceManager2<Material, System::Policy>
////	{
////		MaterialManager(const MaterialManager&);
////		MaterialManager& operator = (const MaterialManager&);		
////	public:
////		MaterialManager() {}
////	};
////}
//
//#endif	//	_H_PUNK_VIRTUAL_MATERIAL_MANAGER