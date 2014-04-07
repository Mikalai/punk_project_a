#ifndef IATTRIBUTE_H
#define IATTRIBUTE_H

#include <typeinfo>
#include <config.h>
#include <string/module.h>

PUNK_ENGINE_BEGIN
namespace Scene {
    class IAttribute
    {
    public:
        virtual ~IAttribute() = 0;
        virtual std::uint64_t GetTypeID() const = 0;
        virtual const Core::String& GetName() const = 0;
        virtual void SetName(const Core::String& name) = 0;
        virtual void* GetRawData() const = 0;
        virtual void SetRawData(void* value) = 0;
        virtual IAttribute* Clone() const = 0;

        template<class T>
        T* Get() {
            return (T*)GetRawData();
        }

        template<class T>
        void Set(T* value) {
            SetRawData((void*)value);
        }
    };

    inline IAttribute::~IAttribute() {}
}
PUNK_ENGINE_END

#endif // IATTRIBUTE_H
