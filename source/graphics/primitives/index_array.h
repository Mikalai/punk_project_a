#ifndef INDEX_ARRAY_H
#define INDEX_ARRAY_H


#include <vector>
#include <config.h>
#include "iindex_array.h"

PUNK_ENGINE_BEGIN
namespace Graphics {


    template<typename IndexType> class IndexArray : public IIndexArray  {
    public:

        IndexArray(const std::vector<IndexType>& array)
            : m_array(array) {}

        IndexArray(IndexType* buffer, std::uint64_t size) {
            m_array.resize(size);
            for (auto i = 0; i < size; ++i) {
                m_array.push_back(*((IndexType*)buffer+i));
            }
        }

        virtual ~IndexArray() {}

		//	IObject
		void QueryInterface(const Core::Guid& type, void** object) {
			Core::QueryInterface(this, type, object, { Core::IID_IObject, IID_IIndexArray });
		}

		std::uint32_t AddRef() override {
			return m_ref_count.fetch_add(1);
		}

		std::uint32_t Release() override {
			auto v = m_ref_count.fetch_sub(1) - 1;
			if (!v)
				delete this;
			return v;
		}
		
		//	IIndexArray
        std::uint64_t GetIndexSize() const override {
            return sizeof(IndexType);
        }

        std::uint64_t GetIndexCount() const override {
            return m_array.size();
        }

        std::uint64_t GetMemoryUsage() const override {
            return GetIndexCount()*GetIndexSize();
        }

        IndexType* GetIndexBuffer() {
            return &m_array[0];
        }

        const IndexType* GetIndexBuffer() const {
            return &m_array[0];
        }
    private:
		
		void* GetBuffer() override {
			return (void*)&m_array[0];
		}

		const void* GetBuffer() const override {
			return (const void*)&m_array[0];
		}

		std::atomic<std::uint32_t> m_ref_count{ 0 };
        std::vector<IndexType> m_array;
    };

	template<> class IndexArray < std::nullptr_t > {};
}
PUNK_ENGINE_END

#endif // INDEX_ARRAY_H
