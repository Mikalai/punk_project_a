#include <core/ifactory.h>
#include <math/vec3.h>
#include <math/vec4.h>
#include <math/mat4.h>
#include <math/quat.h>
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

	template<class Key>
	class KeyFrameImpl : public IKeyFrame {
	public:
		KeyFrameImpl();
		
		//	IObject
		 void QueryInterface(const Core::Guid& type, void** object) override;
		 std::uint32_t AddRef() override;
		 std::uint32_t Release() override;

		//	IKeyFrame
		 std::int32_t GetFrame() const override;
		 void SetFrame(std::int32_t value) override;
		 void GetKey(void* buffer, std::uint32_t size) override;
		 void SetKey(const void* buffer, std::uint32_t size) override;

	private:
		std::atomic<std::uint32_t> m_ref_count{ 1 };
		std::int32_t m_frame{ 0 };
		Key m_key{ Key{} };
	};

	template<class Key>
	KeyFrameImpl<Key>::KeyFrameImpl() {}

	template<class Key>
	void KeyFrameImpl<Key>::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, {Core::IID_IObject, IID_IKeyFrame, InterfaceAccessor<Key>::GetGuid() });
	}
	
	template<class Key>
	std::uint32_t KeyFrameImpl<Key>::AddRef() {
		return m_ref_count.fetch_add(1);
	}

	template<class Key>
	std::uint32_t KeyFrameImpl<Key>::Release() {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v)
			delete this;
		return v;
	}

	//	IKeyFrame
	template<class Key>
	std::int32_t KeyFrameImpl<Key>::GetFrame() const {
		return m_frame;
	}

	template<class Key>
	void KeyFrameImpl< Key>::SetFrame(std::int32_t value) {
		m_frame = value;
	}
	
	template<class Key>
	void KeyFrameImpl<Key>::GetKey(void* buffer, std::uint32_t size) {
		if (size != sizeof(Key))
			throw System::Error::SystemException("Different size");
		memcpy(buffer, &m_key, size);
	}
	
	template<class Key>
	void KeyFrameImpl<Key>::SetKey(const void* buffer, std::uint32_t size) {
		if (size != sizeof(Key))
			throw System::Error::SystemException("Different size");
		memcpy(&m_key, buffer, size);
	}

	PUNK_REGISTER_CREATOR(IID_IFloatKeyFrame, (Core::CreateInstance < KeyFrameImpl<float>, IKeyFrame>));
	PUNK_REGISTER_CREATOR(IID_IVec3KeyFrame, (Core::CreateInstance < KeyFrameImpl<Math::vec3>, IKeyFrame>));
	PUNK_REGISTER_CREATOR(IID_IVec4KeyFrame, (Core::CreateInstance < KeyFrameImpl<Math::vec4>, IKeyFrame>));
	PUNK_REGISTER_CREATOR(IID_IQuatKeyFrame, (Core::CreateInstance < KeyFrameImpl<Math::quat>, IKeyFrame>));
	PUNK_REGISTER_CREATOR(IID_IMat4KeyFrame, (Core::CreateInstance < KeyFrameImpl<Math::mat4>, IKeyFrame>));
}
PUNK_ENGINE_END
