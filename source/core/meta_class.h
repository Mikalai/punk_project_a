#ifndef STATIC_INFORMATION_H
#define STATIC_INFORMATION_H

#include <iostream>
#include <map>
#include "string/string.h"
#include "meta_class_base.h"
#include "object.h"

namespace Punk {
    namespace Engine {
        namespace Core {

            template<class T>
            struct PUNK_ENGINE_LOCAL Class : public ClassBase
            {
            public:
                typedef std::vector<T*> InstanceCollection;

                void Add(Object* value) override
                {
                    value->SetLocalIndex(Instances.size());
                    Instances.push_back((T*)value);
                }

                void Remove(Object* value) override
                {
                    T* o = Instances.back();
                    if (o != value)
                    {
                        Instances[value->GetLocalIndex()] = o;
                        o->SetLocalIndex(value->GetLocalIndex());
                    }
                    Instances.pop_back();
                    if (Instances.empty())
                        Destroy();
                }

                size_t GetInstanceCount() const override
                {
                    return Instances.size();
                }

                Object* GetInstance(size_t index) const override
                {
                    return Instances[index];
                }

                ~Class()
                {
                    while (!Instances.empty())
                    {
                        delete Instances.back();
                        //  Instances.pop_back(); not required, because when
                        //  destructor will be called, object will be popped automatically
                    }
                }

                static void Destroy()
                {
                    delete m_instance;
                    m_instance = nullptr;
                }

                static Class<T>* Instance()
                {
                    if (!m_instance)
                        m_instance = new Class<T>;
                    return m_instance;
                }

            public:
                static Class<T>* m_instance;
                InstanceCollection Instances;
            };

            template<class T>
            Class<T>* Class<T>::m_instance = nullptr;

            //    class Factory
            //    {
            //    public:
            //        static Object* Create(unsigned id);
            //        static void Save(Buffer* buffer, const Object* o);
            //        static Object* Load(Buffer* buffer);
            //        static void Add(size_t id, Object* (*F)());
            //        static void Add(size_t id, void (*F)(Buffer*, const Object*));
            //        static void Add(size_t id, void (*F)(Buffer*, Object*));
            //    private:
            //        static std::map<size_t, Object*(*)()> m_creator;
            //        static std::map<size_t, void (*)(Buffer*, const Object*)> m_saver;
            //        static std::map<size_t, void (*)(Buffer*, Object*)> m_loader;
            //    };

            //    template<class T>
            //    struct StaticInformation
            //    {
            //        typedef std::vector<T*> InstanceCollection;
            //        StaticInformation<T>(const string& name, size_t uid, Object* (*Create)(), void (*Save)(Buffer*, const Object*), void (*Load)(Buffer*, Object*), const Rtti* parent)
            //            : Type(name, uid, parent)
            //        {
            //            if (Create)
            //                Factory::Add(Type.GetId(), T::Create);
            //            if (Save)
            //                Factory::Add(Type.GetId(), Save);
            //            if (Load)
            //                Factory::Add(Type.GetId(), Load);
            //        }

            //        void Add(T* value)
            //        {
            //            value->SetLocalIndex(Instances.size());
            //            Instances.push_back(value);
            //        }

            //        void Remove(T* value)
            //        {
            //            T* o = Instances.back();
            //            if (o != value)
            //            {
            //                Instances[value->GetLocalIndex()] = o;
            //                o->SetLocalIndex(value->GetLocalIndex());
            //            }
            //            Instances.pop_back();
            //        }

            //        void DestroyAllInstances()
            //        {
            //            while (!Instances.empty())
            //            {
            //                delete Instances.back();
            //                // Instances.pop_back(); not required, because when
            //                //  destructor will be called, object will be popped automatically
            //            }
            //        }

            //        Rtti Type;
            //        InstanceCollection Instances;
            //    };
        }
    }
}

#endif // STATIC_INFORMATION_H
