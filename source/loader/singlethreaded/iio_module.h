#ifndef _H_IIO_MODULE
#define _H_IIO_MODULE

#include <config.h>
#include <system/module/module.h>

PUNK_ENGINE_BEGIN
namespace IoModule {

	DECLARE_PUNK_GUID(IID_IIoModule, "AFB6AF9C-01A6-4BF5-923F-9ABC2510C4FC");

	class IIoModule : public System::IModule {
	public:
		virtual Core::Pointer<Core::IObject> Parse(const Core::String& path) = 0;
		virtual Core::Pointer<Core::IObject> Parse(Core::Buffer& buffer) = 0;
		virtual void Serialize(Core::Pointer<Core::IObject> object, const Core::String& path) = 0;
		virtual void Serialize(Core::Pointer<Core::IObject> object, Core::Buffer& buffer) = 0;
		virtual Core::Pointer<Core::IObject> Deserialize(const Core::String& path) = 0;
		virtual Core::Pointer<Core::IObject> Deserialize(Core::Buffer& buffer) = 0;
	};
}
PUNK_ENGINE_END


#endif	//	_H_IIO_MODULE