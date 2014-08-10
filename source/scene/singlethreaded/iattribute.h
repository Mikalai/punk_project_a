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
	DECLARE_PUNK_GUID(CLSID_Attribute, "0DF57D9D-7D10-4657-99CB-288E65BC2037");

	class INode;

    class IAttribute : public Core::IObject
    {
    public:
		virtual INode* GetOwner() const = 0;
		virtual void SetOwner(INode* value) = 0;
		virtual void Initialize(const Core::String& name, Core::Pointer<Core::IObject> value) = 0;
        virtual const Core::String& GetName() const = 0;
        virtual void SetName(const Core::String& name) = 0;
        virtual Core::Pointer<Core::IObject> GetRawData() = 0;
        virtual void SetRawData(Core::Pointer<Core::IObject> value) = 0;
		virtual void OnUpdate(Core::ActionBase<Core::Pointer<IAttribute>>* action) = 0;

        template<typename T>
		Core::Pointer<T> Get() {
			Core::Pointer<T> object = GetRawData();
			return object;
        }

        template<class T>
        void Set(Core::Pointer<T> value) {
            SetRawData(value);
        }

		template<class T>
		void Initialize(const Core::String& name, Core::Pointer<T> value) {
			Initialize(name, Core::Pointer < Core::IObject > {value});
		}
    };    
}
PUNK_ENGINE_END

#endif // IATTRIBUTE_H
