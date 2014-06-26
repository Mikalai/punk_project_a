#ifndef IATTRIBUTE_H
#define IATTRIBUTE_H

#include <typeinfo>
#include <config.h>
#include <core/action.h>
#include <core/iobject.h>
#include <string/module.h>

PUNK_ENGINE_BEGIN
namespace SceneModule {

	DECLARE_PUNK_GUID(IID_IAttribute, "469916D5-2905-4FCE-8054-B2BCA2FF6EE8");
    class IAttribute : public Core::IObject
    {
    public:
        virtual std::uint64_t GetTypeID() const = 0;
        virtual const Core::String& GetName() const = 0;
        virtual void SetName(const Core::String& name) = 0;
        virtual Core::Pointer<Core::IObject> GetRawData() = 0;
        virtual void SetRawData(Core::Pointer<Core::IObject> value) = 0;
		virtual void OnUpdate(Core::ActionBase<IAttribute*>* action) = 0;

        template<typename T>
		Core::Pointer<T> Get() {
			Core::Pointer<T> object{ dynamic_cast<T*>(GetRawData().get()), Code::DestroyObject };
			if (object.get())
				object->AddRef();
			return object;
        }

        template<class T>
        void Set(Core::Pointer<T> value) {
            SetRawData(value);
        }
    };    
}
PUNK_ENGINE_END

#endif // IATTRIBUTE_H
