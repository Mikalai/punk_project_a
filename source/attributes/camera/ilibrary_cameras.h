#ifndef _H_ILIBRARY_CAMERAS
#define _H_ILIBRARY_CAMERAS

#include <config.h>
#include "icamera.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_ILibraryCameras, "C511F259-66E8-4526-8C4E-C2FBF921FF72");
	DECLARE_PUNK_GUID(CLSID_LibraryCameras, "82DCAF1B-91D1-4BCE-8A09-7B70D9272488");

	class ILibraryCameras : public Core::IObject {
	public:
		virtual void SetId(const Core::String& value) = 0;
		virtual const Core::String GetId() const = 0;
		virtual void SetName(const Core::String& value) = 0;
		virtual const Core::String GetName() const = 0;

		virtual void AddCamera(ICamera2Ptr value) = 0;
		virtual std::uint32_t GetCamerasCount() const = 0;
		virtual ICamera2Ptr GetCamera(std::uint32_t index) const = 0;
	};

	using ILibraryCamerasPtr = Core::Pointer < ILibraryCameras > ;

	inline ILibraryCamerasPtr NewLibraryCameras() {
		return System::CreateInstancePtr<ILibraryCameras>(CLSID_LibraryCameras, IID_ILibraryCameras);
	}
}
PUNK_ENGINE_END

#endif	//	_H_ILIBRARY_CAMERAS