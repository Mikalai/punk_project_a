#include <map>
#include <core/iobject_impl.h>
#include <system/factory/module.h>
#include "istyle_set.h"
#include "istyle.h"

PUNK_ENGINE_BEGIN
namespace Gui {

	class StyleSet : public IStyleSet {
	public:
		StyleSet() {}

		~StyleSet() {}

		void QueryInterface(const Core::Guid& type, void** object) override {
			Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IStyleSet });
		}

		std::uint32_t AddRef() override {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() override {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v)
				delete this;
			return v;
		}

		Core::Pointer<IStyle> GetStyle(const Core::String& type) override { 
			auto it = m_style.find(type); 
			if (it == m_style.end())
				return Core::Pointer < IStyle > {nullptr, Core::DestroyObject};
			return it->second;
		}

		void SetStyle(const Core::String& type, Core::Pointer<IStyle> value) override { 
			m_style[type] = value; 
		}

		void SetName(const Core::String& value) override { 
			m_name = value; 
		}

		const Core::String& GetName() const override { 
			return m_name; 
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Core::String m_name;
		std::map<Core::String, Core::Pointer<IStyle>> m_style;
	};

	PUNK_REGISTER_CREATOR(IID_IStyleSet, (System::CreateInstance<StyleSet, IStyleSet>));
}
PUNK_ENGINE_END
