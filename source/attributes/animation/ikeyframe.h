#ifndef _H_IKEYFRAME
#define _H_IKEYFRAME

#include <config.h>
#include <cstdint>
#include <core/iobject.h>

PUNK_ENGINE_BEGIN
namespace Attributes {
	
	DECLARE_PUNK_GUID(IID_IKeyFrame, "D61A0664-77DC-4355-A9F1-C369B5CDC3BD");
	DECLARE_PUNK_GUID(IID_IFloatKeyFrame, "404E0BBF-446A-451A-A011-361C7C9BEAD5");
	DECLARE_PUNK_GUID(IID_IVec3KeyFrame, "66C43E00-73E8-4B43-8C93-7F04D9607AEE");
	DECLARE_PUNK_GUID(IID_IVec4KeyFrame, "AC10C700-E90C-4A52-A19D-73AB7B1052AD");
	DECLARE_PUNK_GUID(IID_IQuatKeyFrame, "D3800214-3866-4B38-B8BF-51281C385390");
	DECLARE_PUNK_GUID(IID_IMat4KeyFrame, "79BF98C0-A080-4CD4-887F-8172BF9463AE");
	
	DECLARE_PUNK_GUID(CLSID_FloatKeyFrame, "6DFE5586-4178-44A4-9814-51DDA00A33C0");
	DECLARE_PUNK_GUID(CLSID_Vec3KeyFrame, "AE438C56-FE1F-4273-9E58-EC105BC3824C");
	DECLARE_PUNK_GUID(CLSID_Vec4KeyFrame, "AFAA9839-8C33-4ED3-B97A-69DE10C984C6");
	DECLARE_PUNK_GUID(CLSID_QuatKeyFrame, "FF6E5183-52BB-4BA4-AAC6-58354F86BF2E");
	DECLARE_PUNK_GUID(CLSID_Mat4KeyFrame, "5CD2B146-6363-4B0D-8C6D-1617FCFB5934");

	class IKeyFrame : public Core::IObject {
	public:
		virtual std::int32_t GetFrame() const = 0;
		virtual void SetFrame(std::int32_t value) = 0;
		virtual void GetKey(void* buffer, std::uint32_t size) const = 0;
		virtual void SetKey(const void* buffer, std::uint32_t size) = 0;
	};

	using IKeyFramePointer = Core::Pointer < IKeyFrame > ;

	template<typename T> 
	class KeyFrame : public IKeyFrame {
	public:

		const T Key() const {
			T key;
			GetKey(&key, sizeof(key));
			return key;
		}

		void Key(const T& value) {
			SetKey(&value, sizeof(value));
		}
	};
}
PUNK_ENGINE_END

#endif	//	_H_IKEYFRAME