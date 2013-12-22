#include <algorithm>
#include <set>
#include <list>
#include <vector>
#include <iostream>
#include <core/core_error.h>
#include <core/object.h>
#include "string/string.h"
#include "string/string_list.h"
#include "component.h"
#include "components_pool.h"

PUNK_ENGINE_BEGIN
namespace Core {

	namespace __private {
		struct ComponentImpl {
			String m_name;
			StringList m_services;
			bool m_initialized{ false };
			bool m_initializing{ false };
			unsigned m_ref_count{ 0 };
			std::set<Object*> m_objects;

			ComponentImpl(const String& name, const StringList& services)
				: m_name(name)
				, m_services(services) {}

			~ComponentImpl() {
			}
		};
	}

	Component::Component(const String& name, const StringList& services)
		: impl(new __private::ComponentImpl(name, services)) {}

	Component::~Component() {
		delete impl;
		impl = nullptr;
	}

    Object* Component::Execute(const String& command, Object** parameters) {

    }

    const String Component::Execute(const String& command) {
        if (command == "get_name") {
            return impl->m_name;
        }
        return "error";
    }
}
PUNK_ENGINE_END
