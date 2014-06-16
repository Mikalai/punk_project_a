#ifndef IATTRIBUTE_H
#define IATTRIBUTE_H

#include <typeinfo>
#include <config.h>
#include <core/action.h>
#include <core/iobject.h>
#include <string/module.h>

PUNK_ENGINE_BEGIN
namespace SceneModule {
    class IAttribute
    {
    public:
        virtual ~IAttribute() = 0;
        virtual std::uint64_t GetTypeID() const = 0;
        virtual const Core::String& GetName() const = 0;
        virtual void SetName(const Core::String& name) = 0;
        virtual Core::IObject* GetRawData() const = 0;
        virtual void SetRawData(Core::IObject* value) = 0;
		virtual void OnUpdate(Core::ActionBase<IAttribute*>* action) = 0;

        template<typename T>
		T* Get() {
			T* object = dynamic_cast<T*>(GetRawData());
			return object;
        }

        template<class T>
        void Set(T* value) {
            SetRawData(value);
        }
    };

    inline IAttribute::~IAttribute() {}
}
PUNK_ENGINE_END

#endif // IATTRIBUTE_H
