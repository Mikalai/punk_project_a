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

        std::uint64_t GetIndexSize() const override {
            return sizeof(IndexType);
        }

        std::uint64_t GetIndexCount() const override {
            return m_array.size();
        }

        std::uint64_t GetMemoryUsage() const override {
            return GetIndexCount()*GetIndexSize();
        }

        void* GetIndexBuffer() override {
            return (void*)&m_array[0];
        }

        const void* GetIndexBuffer() const override {
            return (const void*)&m_array[0];
        }
    private:
        std::vector<IndexType> m_array;
    };
}
PUNK_ENGINE_END

#endif // INDEX_ARRAY_H
