#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <memory>
#include <system/logger/module.h>
#include "iattribute.h"

PUNK_ENGINE_BEGIN
namespace SceneModule {

    template<class T>
    class Attribute : public IAttribute
    {
    public:
		inline Attribute(const Core::String &name, Core::Pointer<T> value)
			: m_name(name)
			, m_data(value)
		{}

		inline Attribute()
			: m_name{}
			, m_data(nullptr)
		{}

		inline ~Attribute() {
			System::GetDefaultLogger()->Info("Destroy attribute " + m_name);
			while (!m_update_actions.empty()) {
				m_update_actions.back()->Release();
				m_update_actions.pop_back();
			}
		}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) {
			Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IAttribute });
		}

		std::uint32_t AddRef() {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v) {
				delete this;
			}
			return v;
		}

		//	IAttribute		
		inline std::uint64_t GetTypeID() const {
			return typeid(T).hash_code();
		}

		inline const Core::String& GetName() const {
			return m_name;
		}

		inline void SetName(const Core::String& value) {
			m_name = value;
		}

		inline Core::Pointer<Core::IObject> GetRawData() {
			Core::IObject* o = dynamic_cast<Core::IObject*>(m_data.get());
			if (o) {
				Core::Pointer<Core::IObject> result{ o, Core::DestroyObject };
				return result;
			}
			return Core::Pointer < Core::IObject > {nullptr, Core::DestroyObject};
		}

		inline void SetRawData(Core::Pointer<Core::IObject> value) {
			Core::Pointer<T> o{ dynamic_cast<T*>(value.get()), Core::DestroyObject };
			if (o.get()) {
				m_data.reset(o.release());
			}
			for (auto action : m_update_actions) {
				(*action)(Core::Pointer < IAttribute > {this, Core::DestroyObject});
			}
		}

		inline void OnUpdate(Core::ActionBase<Core::Pointer<IAttribute>>* action) {
			action->AddRef();
			m_update_actions.push_back(action);
		}

    private:        
		std::atomic<std::uint32_t> m_ref_count{ 0 };
        Core::String m_name;
		Core::Pointer<T> m_data{ nullptr, Core::DestroyObject };
		std::vector < Core::ActionBase<Core::Pointer<IAttribute>>*> m_update_actions;
    };	
}
PUNK_ENGINE_END

#endif // ATTRIBUTE_H
