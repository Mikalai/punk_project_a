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
        Attribute();
		Attribute(const Core::String& name, Core::Pointer<T> value);
        virtual ~Attribute();

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) override;
		std::uint32_t AddRef() override;
		std::uint32_t Release() override;

		//	IAttribute
        std::uint64_t GetTypeID() const override;
        const Core::String& GetName() const override;
        void SetName(const Core::String& name) override;
        Core::Pointer<Core::IObject> GetRawData() override;
        void SetRawData(Core::Pointer<Core::IObject> value) override;
		void OnUpdate(Core::ActionBase<IAttribute*>* action) override;

    private:        
		std::atomic<std::uint32_t> m_ref_count{ 0 };
        Core::String m_name;
		Core::Pointer<T> m_data{ nullptr, Core::DestroyObject };
		std::vector < Core::ActionBase<IAttribute*>*> m_update_actions;
    };

	template<class T>
	void Attribute<T>::QueryInterface(const Core::Guid& type, void** object) {
		Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IAttribute });
	}

	template<class T>
	std::uint32_t Attribute<T>::AddRef() {
		return m_ref_count.fetch_add(1);
	}

	template<class T>
	std::uint32_t Attribute<T>::Release() {
		auto v = m_ref_count.fetch_sub(1) - 1;
		if (!v) {
			delete this;
		}
		return v;
	}

    template<class T>
    inline Attribute<T>::Attribute(const Core::String &name, Core::Pointer<T> value)
        : m_name(name)
        , m_data(value)
    {}

    template<class T>
    inline Attribute<T>::Attribute()
        : m_name{}
        , m_data(nullptr)
    {}

    template<class T>
    inline Attribute<T>::~Attribute() {        		
		System::GetDefaultLogger()->Info("Desotroy attrbute " + m_name);
		while (!m_update_actions.empty()) {
			m_update_actions.back()->Release();
			m_update_actions.pop_back();
		}

    }

    template<class T>
    inline std::uint64_t Attribute<T>::GetTypeID() const {
        return typeid(T).hash_code();
    }

    template<class T>
    inline const Core::String& Attribute<T>::GetName() const {
        return m_name;
    }

    template<class T>
    inline void Attribute<T>::SetName(const Core::String& value) {
        m_name = value;
    }

    template<class T>
    inline Core::Pointer<Core::IObject> Attribute<T>::GetRawData() {				
		Core::IObject* o = dynamic_cast<Core::IObject*>(m_data.get());
		if (o) {
			Core::Pointer<Core::IObject> result{ o, Core::DestroyObject };
			return result;
		}
		return Core::Pointer < Core::IObject > {nullptr, Core::DestroyObject};
    }

    template<class T>
    inline void Attribute<T>::SetRawData(Core::Pointer<Core::IObject> value) {
		Core::Pointer<T> o{ dynamic_cast<T*>(value.get), Core::DestroyObject };
		if (o.get()) {
			m_data.reset(o.release());
		}
		for (auto action : m_update_actions) {
			(*action)(this);
		}
    }

	template<class T>
	inline void Attribute<T>::OnUpdate(Core::ActionBase<IAttribute*>* action) {
		action->AddRef();
		m_update_actions.push_back(action);
	}
}
PUNK_ENGINE_END

#endif // ATTRIBUTE_H
