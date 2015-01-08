#ifndef _H_IACCSESSOR
#define _H_IACCSESSOR

#include <config.h>
#include <core/iobject.h>
#include <math/forward.h>
#include "iparam.h"
#include "iarray.h"

PUNK_ENGINE_BEGIN
namespace Attributes {

	DECLARE_PUNK_GUID(IID_IAccessor, "5794F519-3809-4483-8538-AB734698EC30");	
	DECLARE_PUNK_GUID(CLSID_Accessor, "BE2F0EA4-A7CF-4A6A-80DB-FCE56D0E4378");	

	class IParam;

	class IAccessor : public Core::IObject {
	public:
		virtual void SetCount(std::uint32_t value) = 0;
		virtual std::uint32_t GetCount() const = 0;
		virtual void SetSource(const Core::String& value) = 0;
		virtual const Core::String& GetSource() const = 0;
		virtual void SetStride(std::uint32_t value) = 0;
		virtual std::uint32_t GetStride() const = 0;
		virtual void SetOffset(std::uint32_t value) = 0;
		virtual std::uint32_t GetOffset() const = 0;

		virtual std::uint32_t GetParamsCount() const = 0;
		virtual void SetParamsCount(std::uint32_t value) = 0;
		virtual IParam* GetParam(std::uint32_t index) = 0;
		virtual const IParam* GetParam(std::uint32_t index) const = 0;
		virtual void SetParam(std::uint32_t index, Core::Pointer<IParam> value) = 0;
		virtual void AddParam(Core::Pointer<IParam> value) = 0;
	};

	using IAccessorPtr = Core::Pointer < IAccessor > ;

	template<class Type, int Dim, class Tag> 
	class Accessor {
	public:
		
		Accessor(IAccessor* accessor, IArray* array)
			: m_array{ array }
			, m_accessor{ accessor }
		{}

		bool IsValid() {
			auto count = GetParamsCount();
			if (count != Dim)
				return false;
			if (!m_accessor)
				return false;
			if (!m_array)
				return false;
			for (int i = 0; i < Dim; ++i) {
				if (m_accessor->GetParam(0)->GetType() != ParamTypeAccessor<Type>::Value)
					return false;
			}
			return true;
		}

		const Math::Tuple<Type, Dim, Tag> GetItem(int index) const {
			Type* values = (Type*)m_array->Data();

			Math::Tuple<Type, Dim, Tag> res;
			for (int i = 0; i < Dim; ++i) {
				res[i] = values[m_accessor->GetOffset() + index * m_accessor->GetStride() + i];
			}
			return res;
		}

		void SetItem(int index, const Math::Tuple<Type, Dim, Tag>& value) {
			Type* values = (Type*)m_array->Data();

			for (int i = 0; i < Dim; ++i) {
				values[m_accessor->GetOffset() + index * m_accessor->GetStride() + i] = value[i];
			}
		}

	private:
		Core::Pointer<IAccessor> m_accessor{ Core::make_ptr((IAccessor*)nullptr) };
		Core::Pointer<IArray> m_array{ Core::make_ptr((IArray*)nullptr) };
	};
	
}
PUNK_ENGINE_END

#endif	//	_H_IACCSESSOR