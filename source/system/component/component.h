#ifndef COMPONENT_H
#define COMPONENT_H

#include <initializer_list>
#include "config.h"
#include "string/string.h"

namespace System
{
    class Object;

    class ComponentsPool;

    class PUNK_ENGINE_API Component
    {
    public:
        virtual ~Component() {}                

        const string GetName() const;
        const StringList GetServicesList() const;
        Object* GetService(const string& name);
        void AddDependency(std::initializer_list<string> components);
        void Initialize();
        void Attach();
        /**
         * @brief Detach
         * @return true if destroyed
         */
        bool Detach();

    protected:
        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnInitialize() {}
        virtual Object* OnGetService(const string&) {return nullptr; }

        void AddService(const string& service);
        void SetName(const string& name);

    protected:
        std::vector<string> m_dependency;
        bool m_initialized {false};
        bool m_initializing {false};
        StringList m_services;
        string m_name;
        unsigned m_ref_count {0};
        friend class ComponentsPool;
    };
}

#endif // COMPONENT_H
