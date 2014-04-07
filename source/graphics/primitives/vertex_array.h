#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <vector>
#include <config.h>
#include "ivertex_array.h"
#include "vertex.h"

PUNK_ENGINE_BEGIN
namespace Graphics {

    template<typename VertexType> class VertexArray : public IVertexArray {
    public:

        VertexArray(const std::vector<VertexType>& array)
            : m_array(array) {}

        VertexArray(VertexType* buffer, std::uint64_t size) {
            m_array.resize(size);
            for (auto i = 0; i < size; ++i) {
                m_array.push_back(*((VertexType*)buffer+i));
            }
        }

        virtual ~VertexArray() {}

        std::uint64_t GetVertexType() const override {
            return VertexType::Value();
        }

        std::uint64_t GetVertexSize() const override {
            return sizeof(VertexType);
        }

        std::uint64_t GetVertexCount() const override {
            return m_array.size();
        }

        std::uint64_t GetMemoryUsage() const override {
            return GetVertexCount()*GetVertexSize();
        }

        void* GetVertexBuffer() override {
            return (void*)&m_array[0];
        }

        const void* GetVertexBuffer() const override {
            return (const void*)&m_array[0];
        }
    private:
        std::vector<VertexType> m_array;
    };
}
PUNK_ENGINE_END

#endif // VERTEX_ARRAY_H
