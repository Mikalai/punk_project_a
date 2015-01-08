#ifndef _H_IFLOAT_ARRAY
#define _H_IFLOAT_ARRAY

#include <config.h>
#include "iarray.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class IFloatArray;

	namespace __private {
		extern "C" PUNK_ENGINE_API IFloatArray* CreateFloatArray();
	}

	DECLARE_PUNK_GUID(IID_IFloatArray, "2F30E47D-8A6E-485F-9C59-E8EF9B5D2B06");
	DECLARE_PUNK_GUID(CLSID_FloatArray, "A628C7F3-5D43-4B48-8F3E-0E77873666A3");

	class IFloatArray : public IArray {
	public:	
		virtual void SetValue(int index, float value) = 0;
		virtual float GetValue(int index) const = 0;		

		static Core::Pointer<IFloatArray> Create() {
			return Core::Pointer < IFloatArray > {__private::CreateFloatArray(), Core::DestroyObject};
		}		
	};	

	using IFloatArrayPtr = Core::Pointer < IFloatArray > ;

	inline IFloatArrayPtr NewFloatArray() {
		return System::CreateInstancePtr<IFloatArray>(CLSID_FloatArray, IID_IFloatArray);
	}
}
PUNK_ENGINE_END

#endif	//	_H_IFLOAT_ARRAY