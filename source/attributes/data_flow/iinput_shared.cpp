#include <system/factory/module.h>
#include "iinput_shared.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	class InputShared : public IInputShared {
	public:
		virtual ~InputShared() {}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			if (!object)
				return;
			*object = nullptr;

			if (type == Core::IID_IObject) {
				*object = (IAccessor*)this;
				AddRef();
			}
			else if (type == IID_IInput) {
				*object = this;
				AddRef();
			}
			else if (type == IID_IInputShared) {
				*object = this;
				AddRef();
			}
		}

		std::uint32_t AddRef() override {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() override {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v) {
				delete this;
			}
			return v;
		}

		//	IInput
		void SetSemantic(InputSemantic value) override {
			m_semantic = value;
		}

		InputSemantic GetSemantic() const {
			return m_semantic;
		}
		void SetSource(ISourcePtr value) override {
			m_source = value;
		}

		ISourcePtr GetSource() override {
			return m_source;
		}

		const ISourcePtr GetSource() const override {
			return m_source;
		}

		void SetSourceRef(const Core::String& value) override {
			m_source_ref = value;
		}

		const Core::String GetSourceRef() const override {
			return m_source_ref;
		}

		//	IInputShared
		void SetOffset(std::uint32_t value) override {
			m_offset = value;
		}

		std::uint32_t GetOffset() const override {
			return m_offset;
		}

		void SetSet(std::uint32_t value) override {
			m_set = value;
		}

		std::uint32_t GetSet() const override {
			return m_offset;
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Core::String m_source_ref;
		InputSemantic m_semantic{ InputSemantic::Bad };
		ISourcePtr m_source{ nullptr };
		std::uint32_t m_offset{ 0 };
		std::uint32_t m_set{ 0 };
	};

	PUNK_REGISTER_CREATOR(CLSID_InputShared, (System::CreateInstance<InputShared, IInputShared>));
}
PUNK_ENGINE_END