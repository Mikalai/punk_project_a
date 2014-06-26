//#ifndef _H_PUNK_SYSTEM_OBJECT
//#define _H_PUNK_SYSTEM_OBJECT
//
//#include <vector>
//#include <typeinfo>
//#include <string/string.h>
//#include "core_error.h"
//#include "icompound_object.h"
//#include "container.h"
//
//PUNK_ENGINE_BEGIN
//namespace Core {
//
//	class PUNK_ENGINE_LOCAL Object : public ICompoundObject
//	{
//	public:
//		Object(IObject* parent = nullptr);
//		virtual ~Object();
//		void QueryInterface(const Guid& type, void** object) override;
//		std::uint32_t AddRef() override;
//		std::uint32_t Release() override;
//		void SetOwner(ICompoundObject* object) override;
//		ICompoundObject* GetOwner() override;
//		const ICompoundObject* GetOwner() const override;
//		const Core::String ToString() const override;
//		std::uint64_t GetType() override;
//		void AddChild(IObject* object) override;
//		void RemoveChild(IObject* object, bool depth = false) override;
//		void RemoveChild(std::uint32_t index) override;
//		IObject* GetChild(std::uint32_t index) override;
//		const IObject* GetChild(std::uint32_t index) const override;
//		std::uint32_t GetChildrenCount() const override;
//
//		Object(const Object& o) = delete;
//		Object& operator = (const Object& o) = delete;
//
//	private:
//		std::atomic<std::uint32_t> m_ref_count;
//		std::unique_ptr<Container<IObject*, ICompoundObject>> m_container;
//	};
//}
//PUNK_ENGINE_END
//
//
//#endif	//	_H_PUNK_SYSTEM_OBJECT
