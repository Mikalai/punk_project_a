//#ifndef _H_PUNK_VIRTUAL_CAMERA_MANAGER
//#define _H_PUNK_VIRTUAL_CAMERA_MANAGER
//
//#include "../../system/resource_manager.h"
//#include "../../system/environment.h"
//#include "../data/cameras/fps_camera.h"
//
//namespace Attributes
//{		
//	namespace Cameras
//	{
//		class Camera;
//	}
//}
//
//namespace System
//{
//	template<> class PUNK_ENGINE_API Policy<Attributes::Camera>
//	{
//	public:
//		static const Core::String GetResourceFile() { return L"resource"; }
//		static const Core::String GetExtension() { return L"*.fps_camera"; }
//		static const Core::String GetFolder() { return System::Environment::Instance()->GetSoundFolder(); }	
//		static System::ObjectType GetResourceType() { return System::ObjectType::FPS_CAMERA; }
//		static void OnInit() {}
//		static void OnDestroy() {}
//	};
//}
//
//namespace Attributes
//{
//	class PUNK_ENGINE_API CameraManager : public System::ResourceManager2<Cameras::Camera, System::Policy>
//	{
//		CameraManager(const CameraManager&);
//		CameraManager& operator = (const CameraManager&);		
//	public:
//		CameraManager() {}
//	};
//}
//
//#endif	//	_H_PUNK_VIRTUAL_CAMERA_MANAGER