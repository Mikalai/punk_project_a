#ifndef COMPONENT_H
#define COMPONENT_H

#include <config.h>
#include <initializer_list>
#include <string/string_list.h>
#include "component_interface.h"

PUNK_ENGINE_BEGIN
namespace Core {

	namespace __private {
		struct ComponentImpl;
	}

	class Object;
	class ComponentsPool;

	class PUNK_ENGINE_API Component : public IComponent
	{
	public:
		Component(const String& name, const StringList& services);
		Component(const Component&) = delete;
		Component& operator = (const Component&) = delete;
		virtual ~Component();

		virtual Object* Execute(const String& command, Object** parameters) override;
		virtual const String Execute(const String& command) override;

		__private::ComponentImpl* impl{ nullptr };

	protected:

		friend class ComponentsPool;
	};
}
PUNK_ENGINE_END

#endif // COMPONENT_H
