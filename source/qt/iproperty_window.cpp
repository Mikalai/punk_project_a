#include <set>
#include <core/iobject_impl.h>
#include <core/iinterface_accessor.h>
#include <attributes/collection/icollection.h>

#include "itab_holder.h"
#include "iproperty_window.h"
#include "iobject_tab.h"
#include "icollection_tab.h"

PUNK_ENGINE_BEGIN
namespace Gui {

	class PropertyWindow : public IPropertyWindow {
	public:

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override {
			
			if (!object)
				return;

			*object = nullptr;

			if (type == Core::IID_IObject) {
				*object = (Core::IObject*)this;
				AddRef();
			}
			else if (type == IID_IPropertyWindow) {
				*object = (IPropertyWindow*)this;
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

		//	IWidget
		void Show() override {
			m_tabs->Show();
		}

		void Hide() override {
			m_tabs->Hide();
		}

		bool IsVisible() override {
			return m_tabs->IsVisible();
		}

		//	IPropertyWindow
		void SetObject(Core::Pointer<Core::IObject> value) override {
			auto accessor = Core::QueryInterfacePtr<Core::IInterfaceAccessor>(value, Core::IID_IInterfaceAccessor);
			if (!accessor.get())
				return;

			for (std::uint32_t i = 0; i < accessor->GetInterfacesCount(); ++i) {
				auto g = accessor->GetInterface(i);

				if (g == Core::IID_IObject) {
					auto o = Core::Pointer < Core::IObject > {value};
					auto tab = Core::Pointer <Gui::IObjectTab > {CreateIObjectTab(), Core::DestroyObject};
					tab->SetObject(o);
					m_tabs->AddTab("IObject", tab);
				}
				else if (g == Attributes::IID_ICollection) {
					auto o = Core::Pointer < Attributes::ICollection > {value};
					auto tab = Core::Pointer <Gui::ICollectionTab > {CreateCollectionTab(), Core::DestroyObject};
					m_tabs->AddTab("ICollection", tab);
				}
			}
		}

		void AddProperty(const Core::Guid& value) override {
			m_guids.insert(value);
		}

		void RemoveProperty(const Core::Guid& value) override {
			m_guids.erase(value);
		}

	private:
		std::atomic<std::uint32_t> m_ref_count{ 0 };
		Core::Pointer<Core::IObject> m_object;
		std::set<Core::Guid> m_guids;
		Core::Pointer<ITabHolder> m_tabs{ CreateTabHolder(), Core::DestroyObject };
	};

	extern "C" PUNK_ENGINE_API IPropertyWindow* CreatePropertyWindow() {
		return new PropertyWindow{};
	}
}
PUNK_ENGINE_END
