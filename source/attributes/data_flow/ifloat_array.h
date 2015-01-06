#ifndef _H_IFLOAT_ARRAY
#define _H_IFLOAT_ARRAY

#include <config.h>
#include <core/iobject.h>
#include <string/string.h>

PUNK_ENGINE_BEGIN
namespace Attributes {

	class IFloatArray;

	namespace __private {
		extern "C" PUNK_ENGINE_API IFloatArray* CreateFloatArray();
	}

	DECLARE_PUNK_GUID(IID_IFloatArray, "2F30E47D-8A6E-485F-9C59-E8EF9B5D2B06");
	DECLARE_PUNK_GUID(CLSID_FloatArray, "A628C7F3-5D43-4B48-8F3E-0E77873666A3");

	class IFloatArray : public Core::IObject {
	public:
		virtual std::uint32_t GetCount() const = 0;
		virtual void SetCount(std::uint32_t value) = 0;
		virtual const Core::String GetId() = 0;
		virtual void SetId(const Core::String& value) = 0;
		virtual const Core::String GetName() = 0;
		virtual void SetName(const Core::String& value) = 0;
		virtual void SetValue(int index, float value) = 0;
		virtual float GetValue(int index) const = 0;
		virtual void* Data() = 0;
		virtual const void* Data() const = 0;

		static Core::Pointer<IFloatArray> Create() {
			return Core::Pointer < IFloatArray > {__private::CreateFloatArray(), Core::DestroyObject};
		}		
	};	
}
PUNK_ENGINE_END

#endif	//	_H_IFLOAT_ARRAY