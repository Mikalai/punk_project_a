#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <memory>
#include "iattribute.h"

PUNK_ENGINE_BEGIN
namespace SceneModule {

    template<class T>
    class Attribute : public IAttribute
    {
    public:
        Attribute();
        Attribute(const Core::String& name, T* value, bool del = true);
        Attribute(const Core::String& name, const T& value);
        virtual ~Attribute();

        std::uint64_t GetTypeID() const override;
        const Core::String& GetName() const override;
        void SetName(const Core::String& name) override;
        Core::IObject* GetRawData() const override;
        void SetRawData(Core::IObject* value) override;

    private:        
        Core::String m_name;
		Core::UniquePtr<T> m_data{ nullptr, Core::DestroyObject };
        bool m_delete {true};
    };

    template<class T>
    inline Attribute<T>::Attribute(const Core::String &name, T* value, bool del)
        : m_name(name)
        , m_data(value, Core::DestroyObject)
        , m_delete(del)
    {}

    template<class T>
    inline Attribute<T>::Attribute(const Core::String &name, const T& value)
        : m_name(name)
        , m_data(new T(value))
    {}

    template<class T>
    inline Attribute<T>::Attribute()
        : m_name{}
        , m_data(nullptr)
    {}

    template<class T>
    inline Attribute<T>::~Attribute() {
        if (m_delete)
            m_data.reset();
        else
            m_data.release();
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
    inline Core::IObject* Attribute<T>::GetRawData() const {		
		return m_data.get();
    }

    template<class T>
    inline void Attribute<T>::SetRawData(Core::IObject* value) {
		T* o = dynamic_cast<T*>(value);
		if (o)
			m_data.reset(o);
    }
}
PUNK_ENGINE_END

#endif // ATTRIBUTE_H
