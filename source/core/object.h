#ifndef _H_PUNK_SYSTEM_OBJECT
#define _H_PUNK_SYSTEM_OBJECT

#include <vector>
#include <typeinfo>
#include "string/string.h"
#include "core_error.h"
#include "iobject.h"
#include "container.h"

PUNK_ENGINE_BEGIN
namespace Core {

	class PUNK_ENGINE_LOCAL Object : public IObject
	{
	public:
		Object(IObject* parent = nullptr);
		virtual ~Object();
		void SetOwner(IObject* object) override;
		IObject* GetOwner() override;
		const IObject* GetOwner() const override;
		const Core::String ToString() const override;
		std::uint64_t GetType() override;
		void Add(IObject* object) override;
		void RemoveChild(IObject* object, bool depth = false) override;
		void RemoveChild(std::uint32_t index) override;
		IObject* GetChild(std::uint32_t index) override;
		const IObject* GetChild(std::uint32_t index) const override;
		std::uint32_t GetChildrenCount() const override;

		Object(const Object& o) = delete;
		Object& operator = (const Object& o) = delete;

	private:
		Container<IObject> m_container;
	};
}
PUNK_ENGINE_END


#endif	//	_H_PUNK_SYSTEM_OBJECT
