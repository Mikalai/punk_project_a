#include <memory.h>
#include <system/factory/module.h>
#include <math/forward.h>
#include <math/matrix.h>
#include <system/errors/module.h>
#include "ikeyframe.h"

PUNK_ENGINE_BEGIN
namespace Attributes {	

	template<typename T> struct InterfaceAccessor;
	
	template<>
	struct InterfaceAccessor<Math::vec3> {
		static Core::Guid GetGuid() {
			return IID_IVec3KeyFrame;
		}
	};

	template<>
	struct InterfaceAccessor<Math::vec4> {
		static Core::Guid GetGuid() {
			return IID_IVec4KeyFrame;
		}
	};

	template<>
	struct InterfaceAccessor<Math::quat> {
		static Core::Guid GetGuid() {
			return IID_IQuatKeyFrame;
		}
	};

	template<>
	struct InterfaceAccessor<float> {
		static Core::Guid GetGuid() {
			return IID_IFloatKeyFrame;
		}
	};

	template<>
	struct InterfaceAccessor<Math::mat4> {
		static Core::Guid GetGuid() {
			return IID_IMat4KeyFrame;
		}
	};

	template<class T>
	class KeyFrameImpl : public KeyFrame<T> {
	public:
		KeyFrameImpl();
		
		//	IObject
		 void QueryInterface(const Core::Guid& type, void** object) override;
		 std::uint32_t AddRef() override;
		 std::uint32_t Release() override;

		//	IKeyFrame
		 std::int32_t GetFrame() const override;
		 void SetFrame(std::int32_t value) override;
		 void GetKey(void* buffer, std::uint32_t size) const override;
		 void SetKey(const void* buffer, std::uint32_t size) override;

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		std::int32_t m_frame{ 0 };
		T m_key;
	};

	template<class T>
	KeyFrameImpl<T>::KeyFrameImpl() {}

	template<class T>
	void KeyFrameImpl<T>::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, {Core::IID_IObject, IID_IKeyFrame, InterfaceAccessor<T>::GetGuid() });
	}
	
	template<class T>
	std::uint32_t KeyFrameImpl<T>::AddRef() {
		return m_ref_count.fetch_add(1);
	}

	template<class T>
	std::uint32_t KeyFrameImpl<T>::Release() {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v)
			delete this;
		return v;
	}

	//	IKeyFrame
	template<class T>
	std::int32_t KeyFrameImpl<T>::GetFrame() const {
		return m_frame;
	}

	template<class T>
	void KeyFrameImpl<T>::SetFrame(std::int32_t value) {
		m_frame = value;
	}
	
	template<class T>
	void KeyFrameImpl<T>::GetKey(void* buffer, std::uint32_t size) const {
		if (size != sizeof(T))
			throw System::Error::SystemException("Different size");
		memcpy(buffer, &m_key, size);
	}
	
	template<class T>
	void KeyFrameImpl<T>::SetKey(const void* buffer, std::uint32_t size) {
		if (size != sizeof(T))
			throw System::Error::SystemException("Different size");
		memcpy(&m_key, buffer, size);
	}

	PUNK_REGISTER_CREATOR(CLSID_FloatKeyFrame, (System::CreateInstance < KeyFrameImpl<float>, IKeyFrame>));
	PUNK_REGISTER_CREATOR(CLSID_Vec3KeyFrame, (System::CreateInstance < KeyFrameImpl<Math::vec3>, IKeyFrame>));
	PUNK_REGISTER_CREATOR(CLSID_Vec4KeyFrame, (System::CreateInstance < KeyFrameImpl<Math::vec4>, IKeyFrame>));
	PUNK_REGISTER_CREATOR(CLSID_QuatKeyFrame, (System::CreateInstance < KeyFrameImpl<Math::quat>, IKeyFrame>));
	PUNK_REGISTER_CREATOR(CLSID_Mat4KeyFrame, (System::CreateInstance < KeyFrameImpl<Math::mat4>, IKeyFrame>));
}
PUNK_ENGINE_END
